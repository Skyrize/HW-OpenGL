#pragma once
#include "Component.h"
#include "Camera.h"

class CameraTarget :
    public Component
{
private:
	Camera* mainCamera = nullptr;
	Entity* target = nullptr;
public:
	CameraTarget(Entity& parent) : Component(parent) {};

	virtual void Start() override;
	virtual void Update() override;
public:
    Entity* GetTarget() const;
    void SetTarget(Entity* target);

};

