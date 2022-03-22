#include "VertexLayout.h"

VertexLayout::VertexLayout()
	:m_Stride(0)
{
}

void VertexLayout::Push(GLuint type, unsigned int count, GLuint normalized)
{
	m_Elements.push_back({ type, count, normalized });

	switch (type)
	{
	case (GL_FLOAT):
		m_Stride += 4 * count;
		break;
	}
}
