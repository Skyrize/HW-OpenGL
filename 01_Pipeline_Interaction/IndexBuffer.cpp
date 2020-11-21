#include "IndexBuffer.h"
#include "GL/glew.h"

GLint IndexBuffer::binded = -1;
IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void IndexBuffer::Generate(const GLuint* data, GLuint count)
{
	this->count = count;
	glCreateBuffers(1, &rendererID);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	if (binded != rendererID)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	binded = rendererID;
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	binded = 0;
}

GLuint IndexBuffer::GetCount() const
{
    return count;
}

