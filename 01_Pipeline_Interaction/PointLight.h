#pragma once
#include "Component.h"
class PointLight :
    public Component
{
protected:
	GLfloat ambiantConstant = 1.0;
	glm::vec3 ambiantColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLfloat diffuseConstant = 1.0;
	glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLfloat specularConstant = 1.0;
	glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLfloat shininess = 32.0f;
public:
    PointLight(Entity& parent) : Component(parent) {};
};

