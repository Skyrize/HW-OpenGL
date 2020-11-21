#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray
{
private:
	GLuint rendererID = 0;
	static GLint binded;
public:
	VertexArray();
	~VertexArray();

	void Generate();
	void Bind() const;
	void Unbind() const;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddBuffer(const VertexBuffer& vb, const LayoutElement& layoutElement, GLuint index);
};

