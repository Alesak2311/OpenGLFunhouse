#include "VertexArray.h"

GLuint VertexArray::s_BoundID = 0;

VertexArray::VertexArray()
	:m_ID(0)
{
	GLCall(glCreateVertexArrays(1, &m_ID));
	Bind();
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::AddBuffer(VertexBuffer& vb, const VertexLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));

		offset += element.count;
	}
	vb.Unbind();
}

void VertexArray::Bind()
{
	if (s_BoundID == m_ID)
		return;

	GLCall(glBindVertexArray(m_ID));
	s_BoundID = m_ID;
}

void VertexArray::Unbind()
{
	GLCall(glBindVertexArray(0));

	s_BoundID = 0;
}
