#include "Entity.h"

Entity::Entity()
{
	transform = new Transform(*this);
}

Entity::~Entity()
{
	delete(transform);
	for (auto i = components.begin(); i != components.end(); i++) {
		delete(i->second);
	}
}

void Entity::Start()
{
	for (auto comp : this->components)
	{
		comp.second->Start();
	}
}

void Entity::Update()
{
	for (auto comp : this->components)
	{
		comp.second->Update();
	}
}

std::map<std::type_index,Component*> Entity::GetComponents() const
{
    return components;
}

void Entity::SetComponents(std::map<std::type_index,Component*> components)
{
    this->components = components;
}

std::string Entity::GetName() const
{
    return name;
}

void Entity::SetName(std::string name)
{
    this->name = name;
}

Transform* Entity::GetTransform() const
{
    return transform;
}

void Entity::SetTransform(Transform* transform)
{
    this->transform = transform;
}

