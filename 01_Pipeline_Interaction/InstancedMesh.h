#pragma once
#include "Mesh.h"
#include <list>
#include "Transform.h"
class InstancedMesh :
	public Mesh
{
protected:
	std::list<Transform*> instances;
public:
	InstancedMesh(Entity& parent) : Mesh(parent) {};
	~InstancedMesh();

	virtual void Draw() override;
	void AddInstance(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	void AddInstance(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);
};

