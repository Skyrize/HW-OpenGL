#include "Input.h"

Input Input::instance;

GLboolean* Input::GetKeyStatus()
{
	return this->keyStatus;
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
	glfwPollEvents();						// poll callbacks
	PatchMouseDrift();
}

void Input::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) keyStatus[key] = true;
	else if (action == GLFW_RELEASE) keyStatus[key] = false;

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