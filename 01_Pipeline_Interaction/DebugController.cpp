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
	if (keyStatus[GLFW_KEY_I])		movement += transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_K])		movement -= transform->GetFront() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_J])		movement -= transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_L])		movement += transform->GetRight() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_U])	movement += transform->GetUp() * speed * Time::Get().GetDeltaTime();
	if (keyStatus[GLFW_KEY_O])		movement -= transform->GetUp() * speed * Time::Get().GetDeltaTime();
	//std::cout << "movement = " << VTS(movement) << std::endl;
	transform->Translate(movement);

}
