#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::Generate()
{
	glCreateVertexArrays(1, &rendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	GLuint offset = 0;

	for (GLuint i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *)offset);
		offset += element.count * element.typeSize;
	}
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const LayoutElement& layoutElement, GLuint index)
{
	Bind();
	vb.Bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, layoutElement.count, layoutElement.type, layoutElement.normalized, 0, 0);
}
