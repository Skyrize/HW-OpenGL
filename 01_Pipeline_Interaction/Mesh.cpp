#include "Mesh.h"
//#include "util.h"
//#include "debugTimer.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "Transform.h"
#include "RenderModule.h"
#include "Entity.h"
#include "Asset.h"

Mesh::Mesh(Entity &parent)
	: Renderer(parent)
{

}

void Mesh::LoadModel(const std::string& filename, const std::string &material) {
	this->filename = filename;
	this->material = Asset::Get().GetMaterial(material);
	InitMesh(Asset::Get().GetModel(filename));
}
//
//void Mesh::LoadTexture(const std::string& filename)
//{
//	glBindVertexArray(m_vertexArrayObject); //
//	texture.Generate(filename);
//	texture.Bind();
//	RenderModule::Get().GetShader().SetUniform1i("u_Texture", 0);
//	glBindVertexArray(0);
//}

void Mesh::Start()
{


}

void Mesh::Update()
{
}

void Mesh::InitMesh(const IndexedModel& model)
{
	vertexArrayObject.Generate();

	positionVertexBuffer.Generate(&model.positions[0], sizeof(model.positions[0]) * model.positions.size());
	vertexArrayObject.AddBuffer(positionVertexBuffer, { GL_FLOAT, 3, GL_FALSE, sizeof(GL_FLOAT) }, 0);

	texcoordVertexBuffer.Generate(&model.texCoords[0], sizeof(model.texCoords[0]) * model.texCoords.size());
	vertexArrayObject.AddBuffer(texcoordVertexBuffer, { GL_FLOAT, 2, GL_FALSE, sizeof(GL_FLOAT) }, 1);

	normalVertexBuffer.Generate(&model.normals[0], sizeof(model.normals[0]) * model.normals.size());
	vertexArrayObject.AddBuffer(normalVertexBuffer, { GL_FLOAT, 3, GL_FALSE, sizeof(GL_FLOAT) }, 2);

	indicesVertexBuffer.Generate(&model.indices[0], model.indices.size());

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
}

void Mesh::Draw()
{
	glm::mat4 modelMatrix = transform->GetModelMatrix();
	Shader& shader = RenderModule::Get().GetShader();

	//todo refacto shader materials
	shader.SetUniformMatrix4fv("model_matrix", modelMatrix);

	vertexArrayObject.Bind();
	material->Bind();
	glDrawElements(GL_TRIANGLES, indicesVertexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	//glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

	vertexArrayObject.Unbind();
}

