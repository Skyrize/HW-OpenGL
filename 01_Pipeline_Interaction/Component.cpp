#include "Component.h"
#include "Entity.h"

Component::Component(Entity& parent)
	: parent(parent)
{
	this->transform = parent.GetTransform();
}

void Component::Start()
{
}

void Component::Update()
{
}

Entity& Component::GetParent() const
{
    return parent;
}


Transform* Component::GetTransform() const
{
    return transform;
}

