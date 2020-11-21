#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "OBJLoader.h"
#include "Renderer.h"
#include "Texture.h"

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	COLOR_VB,
	TEXTURE_VB,
	INDEX_VB
};

class Mesh : public Renderer
{
public:
	Mesh(Entity& parent);
	//Mesh(const std::string& fileName);
	//Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void LoadModel(const std::string& filename, const std::string& texture);
	//void LoadTexture(const std::string& filename);
	virtual void Start() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual ~Mesh();
protected:
	//Texture texture;
private:
	void operator=(const Mesh& mesh) {}
	//Mesh(const Mesh& mesh) {}

	std::string filename;

	void InitMesh(const IndexedModel& model);

};