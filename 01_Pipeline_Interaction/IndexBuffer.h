#pragma once
#include "GL/glew.h"
class IndexBuffer
{
private:
	GLuint rendererID = 0;
	GLuint count = 0;
public:
	IndexBuffer();
	~IndexBuffer();

	void Generate(const GLuint* data, GLuint count);
	void Bind() const;
	void Unbind() const;
public:
    GLuint GetCount() const;

};

