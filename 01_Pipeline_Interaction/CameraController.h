#pragma once
#include "Component.h"
#include "Camera.h"
#include "Input.h"

class CameraController :
    public Component
{
protected:
    KeyStatus* keyStatus = nullptr;
    Camera* mainCamera = nullptr;
    GLfloat     speed = 30;

public:
    CameraController(Entity& parent) : Component(parent) {};

    virtual void Start() override;
    virtual void Update() override;

public:
    GLfloat GetSpeed() const;
    void SetSpeed(GLfloat speed);
};

