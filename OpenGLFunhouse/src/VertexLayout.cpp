#include "VertexLayout.h"

VertexLayout::VertexLayout()
	:m_Stride(0)
{
}

void VertexLayout::Push(GLuint type, unsigned int count, GLuint normalized)
{
	m_Elements.push_back({ type, count, normalized });

	m_Stride += m_Elements.back().size;
}

VertexLayoutElement::VertexLayoutElement(GLuint type, unsigned int count, GLuint normalized)
	:type(type), count(count), normalized(normalized), size(0)
{
	switch (type)
	{
	case (GL_FLOAT):
		size = sizeof(float) * count;
		break;

	case (GL_UNSIGNED_INT):
		size = sizeof(unsigned int) * count;
		break;

	default:
		ASSERT(false);
		break;
	}
}
