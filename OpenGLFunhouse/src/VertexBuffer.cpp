#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, const VertexLayout& layout, unsigned int vertexCount)
	:m_ID(0), m_VertexCount(vertexCount)
{
	unsigned int size = layout.GetStride() * m_VertexCount;

	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
