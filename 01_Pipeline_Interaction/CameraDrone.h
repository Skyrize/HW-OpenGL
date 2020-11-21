#pragma once
#include "Component.h"
#include "Camera.h"

class CameraDrone :
    public Component
{
    GLboolean* keyStatus = nullptr;
    Camera* mainCamera = nullptr;
    GLfloat		radius = 10.0f;
    GLfloat		radialSpeed = 0.1f;
    GLfloat     speed = 1;
    glm::vec3   target = glm::vec3(0);

public:
    CameraDrone(Entity& parent) : Component(parent) {};

    virtual void Start() override;
    virtual void Update() override;

    GLfloat GetSpeed() const;
    void SetSpeed(GLfloat speed);
    GLfloat GetRadius() const;
    void SetRadius(GLfloat radius);
    glm::vec3 GetTarget() const;
    void SetTarget(glm::vec3 target);
    GLfloat GetRadialSpeed() const;
    void SetRadialSpeed(GLfloat radialSpeed);

};

