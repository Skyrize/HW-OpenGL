#pragma once
#include <vector>
#include "GL/glew.h"

struct LayoutElement
{
	GLuint type;
	GLuint count;
	GLuint normalized;
	GLuint typeSize;

	LayoutElement(GLuint type, GLuint count, GLuint normalized, GLuint typeSize)
		: type(type), count(count), normalized(normalized), typeSize(typeSize)
	{};
};

class VertexBufferLayout
{
private:
	std::vector<LayoutElement> elements;
	GLuint stride = 0;
public:
	//VertexBufferLayout();

	template <typename T>
	void Push(GLuint count)
	{
		static_assert(false);
	}
	template <>
	void Push<GLfloat>(GLuint count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE, sizeof(GLfloat) });
		stride += sizeof(GLfloat) * count;
	}
	template <>
	void Push<GLuint>(GLuint count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, sizeof(GLuint) });
		stride += sizeof(GLuint) * count;
	}
	template <>
	void Push<GLubyte>(GLuint count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE, sizeof(GLubyte) });
		stride += sizeof(GLubyte) * count;
	}

public:
    std::vector<LayoutElement> GetElements() const;

    GLuint GetStride() const;

};

