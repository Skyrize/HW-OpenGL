#include "CameraController.h"
#include "RenderModule.h"
#include "Entity.h"
#include "Input.h"
#include "Time.h"
#include "Engine.h"


void CameraController::Start()
{
	mainCamera = RenderModule::Get().GetMainCamera();
	keyStatus = Input::Get().GetKeyStatus();
}

void CameraController::Update()
{
	glm::vec3 movement(0);

	if (keyStatus[GLFW_KEY_W] == KeyStatus::PRESSED)		movement += transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_S] == KeyStatus::PRESSED)		movement -= transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_A] == KeyStatus::PRESSED)		movement -= transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_D] == KeyStatus::PRESSED)		movement += transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_SPACE] == KeyStatus::PRESSED)	movement += transform->GetUp() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_Q] == KeyStatus::PRESSED)		movement -= transform->GetUp() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_F] == KeyStatus::PRESSED)			speed = glm::clamp(speed + 0.05f, 0.0f, 200.0f);
	if (keyStatus[GLFW_KEY_G] == KeyStatus::PRESSED)			speed = glm::clamp(speed - 0.05f, 0.0f, 200.0f);
	mainCamera->Move(movement);
}

GLfloat CameraController::GetSpeed() const
{
    return speed;
}

void CameraController::SetSpeed(GLfloat speed)
{
    this->speed = speed;
}
