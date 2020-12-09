#pragma once
#include <string>
#include "Debug.h"
#include <GL/glew.h>			// Add library to extend OpenGL to newest version
#include <GLFW/glfw3.h>  			// Add library to launch a window
#include <GLM/glm.hpp>			// Add helper maths library
#include <GLM/gtx/transform.hpp>

class IObject
{
protected:
	std::string name = "";
	bool isActive = true;
public:
	virtual void Start() = 0;
	virtual void Update() = 0;

	virtual bool IsActive() { return isActive; };
	virtual void SetActive(bool value) { isActive = value; };
};

