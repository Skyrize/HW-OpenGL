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

std::string VTS(glm::vec3 v);
std::string VTS(glm::vec2 v);
std::string MTS(glm::mat4 m);

