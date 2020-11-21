#include "VertexBuffer.h"

GLint VertexBuffer::binded = -1;
VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void VertexBuffer::Generate(const void* data, GLuint size)
{
	glCreateBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
	if (binded != rendererID)
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	binded = rendererID;
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	binded = 0;
}
