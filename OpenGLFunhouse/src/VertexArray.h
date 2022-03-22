#pragma once

#include "VertexBuffer.h"
#include "VertexLayout.h"

class VertexArray
{
private:
	GLuint m_ID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexLayout& layout);

	void Bind() const;
	void Unbind() const;
};