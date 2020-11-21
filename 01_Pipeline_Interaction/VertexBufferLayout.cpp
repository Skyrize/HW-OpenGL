#include "VertexBufferLayout.h"

std::vector<LayoutElement> VertexBufferLayout::GetElements() const
{
    return elements;
}

GLuint VertexBufferLayout::GetStride() const
{
    return stride;
}

