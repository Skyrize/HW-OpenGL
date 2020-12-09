#include "DebugController.h"
#include "RenderModule.h"
#include "Entity.h"
#include "Time.h"
#include "Input.h"

void DebugController::Start()
{
	keyStatus = Input::Get().GetKeyStatus();
}

void DebugController::Update()
{
	glm::vec3 movement(0);
	if (keyStatus[GLFW_KEY_I] == KeyStatus::PRESSED)		movement += transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_K] == KeyStatus::PRESSED)		movement -= transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_J] == KeyStatus::PRESSED)		movement -= transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_L] == KeyStatus::PRESSED)		movement += transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_U] == KeyStatus::PRESSED)	movement += transform->GetUp() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_O] == KeyStatus::PRESSED)		movement -= transform->GetUp() * speed * Time::Get().GetDeltaTime();
	//std::cout << "movement = " << VTS(movement) << std::endl;
	transform->Translate(movement);

}
