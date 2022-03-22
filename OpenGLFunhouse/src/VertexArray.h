#pragma once

#include "VertexBuffer.h"
#include "VertexLayout.h"

class VertexArray
{
private:
	static GLuint s_BoundID;

	GLuint m_ID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexLayout& layout);

	void Bind();
	void Unbind();
};