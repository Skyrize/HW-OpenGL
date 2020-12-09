#pragma once
#include "Component.h"
#include "Input.h"

class DebugComponent : public Component
{
protected:
    KeyStatus* keyStatus = nullptr;
    bool        isWireframe = false;
public:
    DebugComponent(Entity& parent) : Component(parent) {};

    virtual void Start() override;
    virtual void Update() override;

};