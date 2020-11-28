#pragma once
#include "Component.h"
#include "Camera.h"

class LookAtTarget :
	public Component
{
private:
	Entity* target = nullptr;
public:
	LookAtTarget(Entity& parent) : Component(parent) {};

	virtual void Start() override;
	virtual void Update() override;
public:
    Entity* GetTarget() const;
    void SetTarget(Entity* target);

};

