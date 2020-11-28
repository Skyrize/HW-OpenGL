#pragma once
#include "Component.h"
class DebugController :
    public Component
{
private:
	GLboolean* keyStatus = nullptr;
	GLfloat     speed = 3.5f;
public:
	DebugController(Entity& parent) : Component(parent) {};

	virtual void Start() override;
	virtual void Update() override;
};

