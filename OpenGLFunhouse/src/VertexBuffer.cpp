#include "VertexBuffer.h"

GLuint VertexBuffer::s_BoundID = 0;

VertexBuffer::VertexBuffer(const void* data, const VertexLayout& layout, unsigned int vertexCount)
	:m_ID(0), m_VertexCount(vertexCount)
{
	unsigned int size = layout.GetStride() * m_VertexCount;

	GLCall(glGenBuffers(1, &m_ID));
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::Bind()
{
	if (s_BoundID == m_ID)
		return;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	s_BoundID = m_ID;
}

void VertexBuffer::Unbind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	s_BoundID = 0;
}
