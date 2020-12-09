#include "SceneController.h"
#include "Input.h"
#include "RenderModule.h"
#include "Entity.h"
#include "Engine.h"
#include "Manipulate.h"
#include "Animation.h"

void SceneController::Start()
{
	mainCamera = RenderModule::Get().GetMainCamera();
	keyStatus = Input::Get().GetKeyStatus();
	camTarget = mainCamera->GetParent().GetComponent<LookAtTarget>();
	camFPS = mainCamera->GetParent().GetComponent<CameraFPS>();
	camController = mainCamera->GetParent().GetComponent<CameraController>();
	camTransform = mainCamera->GetTransform();
	animated = Engine::Get().GetEntitiesByTag("Animate");
	arrowTransform = Engine::Get().GetEntity("Arrow")->GetTransform();

	for (auto anim : animated) {
		auto childs = anim->GetChilds();

		for (auto child : childs) {
			Animation *childAnim = child->GetComponent<Animation>();
			Transform* t = child->GetTransform();
			glm::vec3 newPos = t->GetPosition() + GetRandomDirection() * 3.0f;

			childAnim->AddClip(Clip("deconstruct", 0.3, Transform(*t), Transform(t->GetPosition(), t->GetRotationEuler(), glm::vec3(0))));
			childAnim->AddClip(Clip("reconstruct", 0.3, Transform(t->GetPosition(), t->GetRotationEuler(), glm::vec3(0)), Transform(*t)));
		}

	}
	SetObservationScene();
}
void SceneController::Focus()
{
	Unselect();
	camTarget->SetActive(true);
	camTarget->SetTarget(animated[currentAnimated]);
	state = SceneState::ANIMATED;
	animated[currentAnimated]->GetComponent<Manipulate>()->SetActive(true);
	animated[currentAnimated]->GetComponent<Animation>()->Play("focus", [this]() {state = SceneState::FOCUSING; });
}

void SceneController::Unfocus()
{
	state = SceneState::ANIMATED;
	animated[currentAnimated]->GetComponent<Manipulate>()->SetActive(false);
	animated[currentAnimated]->GetComponent<Animation>()->Play("unfocus", [this]() {SetObservationScene();});
}

void SceneController::Select()
{
	auto childs = animated[currentAnimated]->GetChilds();
	auto mesh = animated[currentAnimated]->TryGetComponent<Mesh>();

	for (auto child : childs) {
		child->GetComponent<Mesh>()->SetOutlined(true);
	}
	arrowTransform->SetPosition(animated[currentAnimated]->GetTransform()->GetPosition() + glm::vec3(0, 5, 0));
	if (mesh) {
		mesh->SetOutlined(true);
	}
}

void SceneController::Unselect()
{
	auto childs = animated[currentAnimated]->GetChilds();
	auto mesh = animated[currentAnimated]->TryGetComponent<Mesh>();

	for (auto child : childs) {
		child->GetComponent<Mesh>()->SetOutlined(false);
	}
	arrowTransform->SetPosition(glm::vec3(-100000));
	if (mesh) {
		mesh->SetOutlined(false);
	}
}

void SceneController::Deconstruct()
{
	auto childs = animated[currentAnimated]->GetChilds();

	if (childs.size() == 0)
		return;

	state = SceneState::ANIMATED;


	for (int i = 0; i != childs.size(); i++) {
		if (i == currentDeconstructed)
			continue;
		childs[i]->GetComponent<Animation>()->Play("deconstruct", [this]() {state = SceneState::DECONSTRUCTING; });
	}
}

void SceneController::Reconstruct(Callback callback)
{
	auto childs = animated[currentAnimated]->GetChilds();

	if (childs.size() == 0)
		return;
	state = SceneState::ANIMATED;

	for (int i = 0; i != childs.size(); i++) {
		if (i == currentDeconstructed)
			continue;
		if (callback) {
			childs[i]->GetComponent<Animation>()->Play("reconstruct", callback);
		}
		else {
			childs[i]->GetComponent<Animation>()->Play("reconstruct", [this]() {state = SceneState::FOCUSING; });
		}
	}
}


void SceneController::NextDeconstruct()
{
	Reconstruct([this]() {state = SceneState::REBUILD; });
	currentDeconstructed++;
	if (currentDeconstructed == animated[currentAnimated]->GetChilds().size()) {
		currentDeconstructed = 0;
	}
}

void SceneController::PreviousDeconstruct()
{
	Reconstruct([this](){state = SceneState::REBUILD;});
	currentDeconstructed--;
	if (currentDeconstructed == -1) {
		currentDeconstructed = animated[currentAnimated]->GetChilds().size() - 1;
	}
}
void SceneController::SetObservationScene()
{

	state = SceneState::OBSERVING;
	camFPS->SetActive(false);
	camController->SetActive(false);
	camTarget->SetActive(false);
	camTransform->SetPosition(glm::vec3(13, 18.5, -27));
	camTransform->SetRotation(glm::vec3(162, 42, 180));
	Select();
}

void SceneController::SetExplorationScene()
{
	state = SceneState::EXPLORING;
	camFPS->SetActive(true);
	camController->SetActive(true);
	camTarget->SetActive(false);
	Unselect();
}

void SceneController::Next()
{
	Unselect();
	currentAnimated++;
	if (currentAnimated == animated.size()) {
		currentAnimated = 0;
	}
	Select();
}

void SceneController::Previous()
{
	Unselect();
	currentAnimated--;
	if (currentAnimated == -1) {
		currentAnimated = animated.size() - 1;
	}
	Select();
}

void SceneController::Update()
{
	switch (state)
	{
	case SceneState::EXPLORING:
		if (keyStatus[GLFW_KEY_T] == KeyStatus::RELEASED) {
			SetObservationScene();
		}
		break;
	case SceneState::OBSERVING:
		if (keyStatus[GLFW_KEY_T] == KeyStatus::RELEASED) {
			SetExplorationScene();
		}

		if (keyStatus[GLFW_KEY_LEFT] == KeyStatus::RELEASED) {
			Next();
		}
		if (keyStatus[GLFW_KEY_RIGHT] == KeyStatus::RELEASED) {
			Previous();
		}
		if (keyStatus[GLFW_KEY_ENTER] == KeyStatus::RELEASED) {
			Focus();
		}
		break;
	case SceneState::FOCUSING:
		if (keyStatus[GLFW_KEY_ENTER] == KeyStatus::RELEASED) {
			Unfocus();
		}
		if (keyStatus[GLFW_KEY_SPACE] == KeyStatus::RELEASED) {
			Deconstruct();
		}
		break;
	case SceneState::DECONSTRUCTING:
		if (keyStatus[GLFW_KEY_SPACE] == KeyStatus::RELEASED) {
			Reconstruct();
		}
		if (keyStatus[GLFW_KEY_D] == KeyStatus::RELEASED) {
			NextDeconstruct();
		}
		if (keyStatus[GLFW_KEY_S] == KeyStatus::RELEASED) {
			PreviousDeconstruct();
		}
		break;
	case SceneState::REBUILD:
		Deconstruct();
		break;
	case SceneState::ANIMATED:
		break;
	default:
		break;
	}

}
