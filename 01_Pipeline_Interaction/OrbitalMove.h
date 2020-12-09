#pragma once
#include "Component.h"
#include "Camera.h"
#include "Input.h"

class OrbitalMove :
    public Component
{
    KeyStatus* keyStatus = nullptr;
    GLfloat		radius = 4.0f;
    GLfloat     speed = 1;
    glm::vec3   target = glm::vec3(0);

public:
    OrbitalMove(Entity& parent) : Component(parent) {};

    virtual void Start() override;
    virtual void Update() override;

    GLfloat GetSpeed() const;
    void SetSpeed(GLfloat speed);
    GLfloat GetRadius() const;
    void SetRadius(GLfloat radius);
    glm::vec3 GetTarget() const;
    void SetTarget(glm::vec3 target);

};

