// 3D Graphics and Animation - Main Template
// Visual Studio 2019
// Last Changed 01/10/2019

#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")
#define GLM_ENABLE_EXPERIMENTAL
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include <GL/glew.h>			// Add library to extend OpenGL to newest version
#include <GLFW/glfw3.h>  			// Add library to launch a window
#include <GLM/glm.hpp>			// Add helper maths library
#include <GLM/gtx/transform.hpp>

#include <stb_image.h>			// Add library to load images for textures

#include "Mesh.h"				// Simplest mesh holder and OBJ loader - can update more - from https://github.com/BennyQBD/ModernOpenGLTutorial
#include "Asset.h"
#include "Component.h"
#include "Camera.h"
#include "Entity.h"
#include "Engine.h"
#include "Time.h"
#include "Input.h"

int main()
{
												// Start a window using GLFW
	// Fullscreen
	//const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	// windowWidth = mode->width; windowHeight = mode->height; //fullscreen
	// window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), glfwGetPrimaryMonitor(), NULL); // fullscreen

	// Window

	try
	{
		Engine::Get().Init();
		Engine::Get().Start();
		Engine::Get().Update();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		Engine::Get().End();
		return (84);
	}
	Engine::Get().End();
														//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);	// Set mouse cursor. Fullscreen
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// Set mouse cursor FPS fullscreen.


	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}
