#include "Entity.h"

Entity::Entity(Entity *parent /*= nullptr*/)
	: parent(parent)
{
	transform = new Transform(*this);
	if (parent) {
		parent->AddChild(this);
	}
}

Entity::~Entity()
{
	delete(transform);
	for (auto i = components.begin(); i != components.end(); i++) {
		delete(i->second);
	}
}

void Entity::AddChild(Entity* newChild)
{
	if (newChild->parent != this) {
		newChild->parent = this;
	}
	childs.push_back(newChild);
}

Entity* Entity::GetChild(GLuint targetIndex)
{
	if (childs.size() < targetIndex)
		throw ("Index out of bound");
	return childs[targetIndex];
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
		if (comp.second->IsActive()) {
			comp.second->Update();
		}
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


Entity* Entity::GetParent() const
{
    return parent;
}

void Entity::SetParent(Entity* parent)
{
    this->parent = parent;
}

std::vector<Entity*> Entity::GetChilds() const
{
    return childs;
}


std::string Entity::GetTag() const
{
    return tag;
}

void Entity::SetTag(std::string tag)
{
    this->tag = tag;
}

