#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <GL/glew.h>			// Add library to extend OpenGL to newest version
#include <GLFW/glfw3.h>  			// Add library to launch a window
#include <GLM/glm.hpp>			// Add helper maths library
#include <GLM/gtx/transform.hpp>
void ErrorGLFWCallbackBind(int error, const char* description);
void OnResizeCallbackBind(GLFWwindow* window, int w, int h);
void OnKeyCallbackBind(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnMouseButtonCallbackBind(GLFWwindow* window, int button, int action, int mods);
void OnMouseMoveCallbackBind(GLFWwindow* window, double x, double y);
void OnMouseWheelCallbackBind(GLFWwindow* window, double xoffset, double yoffset);
