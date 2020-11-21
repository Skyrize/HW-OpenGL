
#include "Engine.h"
#include "RenderModule.h"

void ErrorGLFWCallbackBind(int error, const char* description) {
	Engine::Get().ErrorGLFWCallback(error, description);
}

void OnResizeCallbackBind(GLFWwindow* window, int w, int h) {
	RenderModule::Get().OnResizeCallback(window, w, h);
}

void OnKeyCallbackBind(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Input::Get().OnKeyCallback(window, key, scancode, action, mods);
}

void OnMouseButtonCallbackBind(GLFWwindow* window, int button, int action, int mods) {
	Input::Get().OnMouseButtonCallback(window, button, action, mods);
}

void OnMouseMoveCallbackBind(GLFWwindow* window, double x, double y) {
	Input::Get().OnMouseMoveCallback(window, x, y);
}

void OnMouseWheelCallbackBind(GLFWwindow* window, double xoffset, double yoffset) {
	Input::Get().OnMouseWheelCallback(window, xoffset, yoffset);
}
