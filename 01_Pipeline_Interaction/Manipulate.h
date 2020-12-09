#pragma once
#include "Component.h"
#include "Transform.h"
#include "Input.h"
class Manipulate :
    public Component
{
private:
    glm::vec3 baseScale = glm::vec3(1);
    glm::vec3 basePosition = glm::vec3(1);
    glm::quat baseRotation = glm::quat(1, 0, 0, 0);
    glm::vec3 rotation = glm::vec3(0);
    GLfloat scale = 1;
    KeyStatus* keyStatus = nullptr;
public:
    Manipulate(Entity& parent) : Component(parent) {};
    virtual void Start() override;
    virtual void Update() override;
    virtual void SetActive(bool active) override;
};

