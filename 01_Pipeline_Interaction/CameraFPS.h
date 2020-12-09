#pragma once
#include "Component.h"
#include "Camera.h"
#include "Input.h"

class CameraFPS :
    public Component
{
protected:
    KeyStatus* keyStatus = nullptr;
    Camera* mainCamera = nullptr;
    GLfloat     sensitivity = 1.0f;
    glm::vec3   rotation = glm::vec3(0);

public:
    CameraFPS(Entity& parent) : Component(parent) {};

    virtual void Start() override;
    virtual void Update() override;

};

