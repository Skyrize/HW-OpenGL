#pragma once
#include "Component.h"
#include <map>
#include <list>
#include <typeindex>
#include "Transform.h"
class Entity : public IObject
{

protected:
	std::string tag = "";
	Entity* parent = nullptr;
	std::vector<Entity*> childs;
	std::map<std::type_index, Component *> components;
	std::string name = "Entity default";
	Transform* transform = nullptr;

public:
	Entity(Entity *parent = nullptr);
	~Entity();

	template <typename T>
	T* GetComponent()
	{
		auto it = components.find(typeid(T));

		if (it == components.end()) {
			throw("Missing component : " + std::string(typeid(T).name()));
		}
		return static_cast<T*>(it->second);
	}

	template <typename T>
	T* TryGetComponent()
	{
		auto it = components.find(typeid(T));

		if (it == components.end()) {
			return nullptr;
		}
		return static_cast<T*>(it->second);
	}

	template <typename T>
	T *AddComponent()
	{
		auto it = components.find(typeid(T));

		if (it != components.end()) {
			throw("2 components of the same type : " + std::string(typeid(T).name()));
		}
		T* newComp = new T(*this);
		this->components[typeid(T)] = newComp;
		return newComp;
	}

	virtual void AddChild(Entity* newChild);
	virtual Entity* GetChild(GLuint targetIndex);

	virtual void Start() override;
	virtual void Update() override;
public:
    std::map<std::type_index,Component*> GetComponents() const;
    void SetComponents(std::map<std::type_index,Component*> components);

    std::string GetName() const;
    void SetName(std::string name);

    Transform* GetTransform() const;
    void SetTransform(Transform* transform);

public:
    Entity* GetParent() const;
    void SetParent(Entity* parent);

    std::vector<Entity*> GetChilds() const;

public:
    std::string GetTag() const;
    void SetTag(std::string tag);

};

