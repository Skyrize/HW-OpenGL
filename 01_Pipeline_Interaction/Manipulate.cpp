#include "Manipulate.h"
#include "Time.h"

void Manipulate::Start()
{
	isActive = false;
	keyStatus = Input::Get().GetKeyStatus();
}

void Manipulate::Update()
{
	if (keyStatus[GLFW_KEY_RIGHT] == KeyStatus::PRESSED) {
		rotation.y += 100 * Time::Get().GetDeltaTime();
	}
	if (keyStatus[GLFW_KEY_LEFT] == KeyStatus::PRESSED) {
		rotation.y -= 100 * Time::Get().GetDeltaTime();
	}
	if (keyStatus[GLFW_KEY_UP] == KeyStatus::PRESSED) {
		rotation.x += 100 * Time::Get().GetDeltaTime();
	}
	if (keyStatus[GLFW_KEY_DOWN] == KeyStatus::PRESSED) {
		rotation.x -= 100 * Time::Get().GetDeltaTime();
	}
	if (keyStatus[GLFW_KEY_N] == KeyStatus::PRESSED) {
		scale += 0.75 * Time::Get().GetDeltaTime();
	}
	if (keyStatus[GLFW_KEY_B] == KeyStatus::PRESSED) {
		scale -= 0.75 * Time::Get().GetDeltaTime();
	}
	transform->SetScale(glm::vec3(scale));
	transform->SetRotation(rotation);

}

void Manipulate::SetActive(bool active)
{
	this->isActive = active;
	if (isActive) {
		this->basePosition = transform->GetPosition();
		this->baseRotation = transform->GetRotation();
		this->baseScale = transform->GetScale();
	}
	else {
		transform->SetPosition(basePosition);
		transform->SetRotation(baseRotation);
		transform->SetScale(baseScale);
	}
}
