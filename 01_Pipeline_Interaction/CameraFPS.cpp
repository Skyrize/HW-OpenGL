#include "CameraFPS.h"
#include "Entity.h"
#include "RenderModule.h"
#include "Time.h"
#include "Input.h"

void CameraFPS::Start()
{
	this->name = "Camera FPS";
	glfwSetInputMode(RenderModule::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	mainCamera = RenderModule::Get().GetMainCamera();
	keyStatus = Input::Get().GetKeyStatus();
	/*rotation = transform->GetRotationEuler();
	rotation.z = 0;*/
	rotation = glm::vec3(0, 0, 0);
}

void CameraFPS::Update()
{
	rotation.x += Input::Get().GetMouseInput().y * sensitivity * Time::Get().GetDeltaTime();
	rotation.y -= Input::Get().GetMouseInput().x * sensitivity * Time::Get().GetDeltaTime();

	// std::cout << "before rot" << VTS(rotation) << std::endl;
	if (rotation.x > 89.0f) rotation.x = 89.0f;
	if (rotation.x < -89.0f) rotation.x = -89.0f;


	transform->SetRotation(rotation);

	//rotation.x += Input::Get().GetMouseInput().x * sensitivity * Time::Get().GetDeltaTime();
	//rotation.y += Input::Get().GetMouseInput().y * sensitivity * Time::Get().GetDeltaTime();

	//if (rotation.y > 89.0f) rotation.y = 89.0f;
	//if (rotation.y < -89.0f) rotation.y = -89.0f;
	//rotation.x = fmod(rotation.x, 360.0f);
	//glm::vec3 direction;
	//direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	//direction.y = sin(glm::radians(rotation.y));
	//direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	////transform->SetFront(glm::normalize(direction));

	//std::cout << "direction " << VTS(direction) << std::endl;
	// std::cout << "rotation : " << VTS(this->rotation) << std::endl;
	// std::cout << "transform rotation : " << VTS(transform->GetRotationEuler()) << std::endl << std::endl;

}