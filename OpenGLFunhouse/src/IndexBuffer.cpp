#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int indexCount)
	:m_ID(0), m_IndexCount(indexCount)
{
	GLCall(glGenBuffers(1, &m_ID));
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_ID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
