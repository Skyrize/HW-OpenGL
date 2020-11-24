#pragma once

#include "GL/glew.h"

class VertexBuffer
{
private:
	GLuint rendererID = 0;
public:
	VertexBuffer();
	~VertexBuffer();

	void Generate(const void* data, GLuint size);
	void Bind() const;
	void Unbind() const;
};

