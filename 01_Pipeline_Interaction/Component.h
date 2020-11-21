#pragma once
#include <string>
#include "IObject.h"

class Entity;
class Transform;

class Component : public IObject
{
protected :
	Entity& parent;
	Transform* transform = nullptr;
	std::string name = "Component default";
public:
	Component(Entity& parent);
	virtual void Start() override;
	virtual void Update() override;
public:
    Entity& GetParent() const;

public:
    Transform* GetTransform() const;

};

