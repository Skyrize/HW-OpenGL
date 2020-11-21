#pragma once
#include "Component.h"
#include "Camera.h"

class CameraController :
    public Component
{
protected:
    GLboolean* keyStatus = nullptr;
    Camera* mainCamera = nullptr;
    GLfloat     speed = 1;

public:
    CameraController(Entity& parent) : Component(parent) {};

    virtual void Start() override;
    virtual void Update() override;

public:
    GLfloat GetSpeed() const;
    void SetSpeed(GLfloat speed);
};

