#include "IndexBuffer.h"

GLuint IndexBuffer::s_BoundID = 0;

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

void IndexBuffer::Bind()
{
	if (s_BoundID == m_ID)
		return;

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	s_BoundID = m_ID;
}

void IndexBuffer::Unbind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	s_BoundID = 0;
}
