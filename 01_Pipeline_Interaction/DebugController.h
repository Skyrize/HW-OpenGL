#pragma once
#include "Component.h"
#include "Input.h"
class DebugController :
    public Component
{
private:
	KeyStatus* keyStatus = nullptr;
	GLfloat     speed = 3.5f;
public:
	DebugController(Entity& parent) : Component(parent) {};

	virtual void Start() override;
	virtual void Update() override;
};

