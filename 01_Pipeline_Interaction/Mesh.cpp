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

void Mesh::LoadModel(const std::string& filename, const std::string &texture) {
	this->filename = filename;
	this->textureID = Asset::Get().GetTextureID(texture);
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
	//m_numIndices = (unsigned int) model.indices.size();

	vertexArrayObject.Generate();

	positionVertexBuffer.Generate(&model.positions[0], sizeof(model.positions[0]) * model.positions.size());
	vertexArrayObject.AddBuffer(positionVertexBuffer, { GL_FLOAT, 3, GL_FALSE, sizeof(GL_FLOAT) }, 0);

	texcoordVertexBuffer.Generate(&model.texCoords[0], sizeof(model.texCoords[0]) * model.texCoords.size());
	vertexArrayObject.AddBuffer(texcoordVertexBuffer, { GL_FLOAT, 2, GL_FALSE, sizeof(GL_FLOAT) }, 1);

	normalVertexBuffer.Generate(&model.normals[0], sizeof(model.normals[0]) * model.normals.size());
	vertexArrayObject.AddBuffer(normalVertexBuffer, { GL_FLOAT, 3, GL_FALSE, sizeof(GL_FLOAT) }, 2);

	colorVertexBuffer.Generate(&model.normals[0], sizeof(model.normals[0]) * model.normals.size());
	vertexArrayObject.AddBuffer(colorVertexBuffer, { GL_FLOAT, 3, GL_FALSE, sizeof(GL_FLOAT) }, 3);

	std::vector<GLfloat> textureIDs(sizeof(GLfloat) * model.normals.size(), this->textureID);
	textureVertexBuffer.Generate(&textureIDs[0], sizeof(GLfloat) * model.normals.size());
	vertexArrayObject.AddBuffer(textureVertexBuffer, { GL_FLOAT, 1, GL_FALSE, sizeof(GL_FLOAT) }, 4);

	indicesVertexBuffer.Generate(&model.indices[0], model.indices.size());


	
	//glGenVertexArrays(1, &m_vertexArrayObject); //
	//glBindVertexArray(m_vertexArrayObject); //

	//glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); //

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]); //
	//glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);//
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOR_VB]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//std::vector<GLfloat> test;
	//for (int i = 0; i != model.normals.size(); i++) {
	//	test.push_back(this->textureID);
	//}
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXTURE_VB]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.normals.size(), &test[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);



	glBindVertexArray(0);
}

//Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
//{
//	IndexedModel model;
//
//	for (unsigned int i = 0; i < numVertices; i++)
//	{
//		model.positions.push_back(*vertices[i].GetPos());
//		model.texCoords.push_back(*vertices[i].GetTexCoord());
//		model.normals.push_back(*vertices[i].GetNormal());
//	}
//
//	for (unsigned int i = 0; i < numIndices; i++)
//		model.indices.push_back(indices[i]);
//
//	InitMesh(model);
//}

Mesh::~Mesh()
{
	//glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glm::mat4 modelMatrix = transform->GetModelMatrix();
	Shader& shader = RenderModule::Get().GetShader();

	//todo refacto shader materials
	shader.SetUniformMatrix4fv("model_matrix", modelMatrix);

	vertexArrayObject.Bind();
	//glBindVertexArray(m_vertexArrayObject);
	//texture.Bind();
	//vertexArrayObject.Bind();
	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, indicesVertexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	//glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

	//glBindVertexArray(0);
	vertexArrayObject.Unbind();
}

