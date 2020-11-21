#pragma once
#include "Component.h"

class DebugComponent : public Component
{
protected:
    GLboolean* keyStatus = nullptr;
    bool        isWireframe = false;
public:
    DebugComponent(Entity& parent) : Component(parent) {};

    virtual void Start() override;
    virtual void Update() override;

};