#include "Input.h"

Input Input::instance;

KeyStatus* Input::GetKeyStatus()
{
	return this->realKeyStatus;
}

glm::vec2 Input::GetMousePosition()
{
	return this->mousePosition;
}

glm::vec2 Input::GetMouseInput()
{
	return this->mouseInput;
}

void Input::Start()
{
}

void Input::Update()
{
	for (int i = 0; i != 1024; i++) {
		if (realKeyStatus[i] == KeyStatus::RELEASED) {
			realKeyStatus[i] = KeyStatus::UP;
		}
	}
	glfwPollEvents();						// poll callbacks
	PatchMouseDrift();
}

void Input::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		keyStatus[key] = true;
		realKeyStatus[key] = KeyStatus::PRESSED;
	}
	else if (action == GLFW_RELEASE) {
		keyStatus[key] = false;
		if (realKeyStatus[key] == KeyStatus::PRESSED) {
			realKeyStatus[key] = KeyStatus::RELEASED;
		}
		else {
			realKeyStatus[key] = KeyStatus::UP;
		}
	}


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Input::OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void Input::OnMouseMoveCallback(GLFWwindow* window, double x, double y) {
	mousePosition = glm::vec2(x, y);

	mouseInput.x = mousePosition.x - lastMousePosition.x;
	mouseInput.y = lastMousePosition.y - mousePosition.y;
	lastMousePosition = mousePosition;
	mouseMoved = true;
}

void Input::OnMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
	int yoffsetInt = static_cast<int>(yoffset);
}


void Input::PatchMouseDrift()
{
	if (mouseMoved == false) {
		mouseInput = glm::vec2(0);
	}
	mouseMoved = false;
}