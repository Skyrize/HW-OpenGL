#pragma once
#include "Component.h"
#include "IRender.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Material.h"

class Renderer :
   public IRender
{
protected:
	//static const unsigned int NUM_BUFFERS = 4;
	VertexArray vertexArrayObject;
	VertexBuffer positionVertexBuffer;
	VertexBuffer texcoordVertexBuffer;
	VertexBuffer normalVertexBuffer;
	IndexBuffer indicesVertexBuffer;

	Material* material = nullptr;
	//GLuint m_vertexArrayObject;
	//GLuint m_vertexArrayBuffers[NUM_BUFFERS] = { 0 };
	//unsigned int m_numIndices = 0;
public:
	Renderer(Entity& parent);
	~Renderer();
	virtual void Start() override;
	virtual void Update() override;

	virtual void Draw() override;

};

