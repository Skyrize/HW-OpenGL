#include "CameraController.h"
#include "RenderModule.h"
#include "Entity.h"
#include "Input.h"
#include "Time.h"

void CameraController::Start()
{
	mainCamera = RenderModule::Get().GetMainCamera();
	keyStatus = Input::Get().GetKeyStatus();
}

void CameraController::Update()
{
	glm::vec3 movement(0);
	if (keyStatus[GLFW_KEY_W])		movement += transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_S])		movement -= transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_A])		movement -= transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_D])		movement += transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_SPACE])	movement += transform->GetUp() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_Q])		movement -= transform->GetUp() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_F])			speed = glm::clamp(speed + 0.05f, 0.0f, 10.0f);
	if (keyStatus[GLFW_KEY_G])			speed = glm::clamp(speed - 0.05f, 0.0f, 10.0f);
	//std::cout << "movement = " << VTS(movement) << std::endl;
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
