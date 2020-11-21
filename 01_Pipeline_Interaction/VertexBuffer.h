#pragma once

#include "GL/glew.h"

class VertexBuffer
{
private:
	GLuint rendererID = 0;
	static GLint binded;
public:
	VertexBuffer();
	~VertexBuffer();

	void Generate(const void* data, GLuint size);
	void Bind() const;
	void Unbind() const;
};

