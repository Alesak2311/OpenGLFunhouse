#pragma once

#include "Tools.h"

#include "VertexLayout.h"

class VertexBuffer
{
private:
	static GLuint s_BoundID;

	GLuint m_ID;
	unsigned int m_VertexCount;
public:
	VertexBuffer(const void* data, const VertexLayout& layout, unsigned int vertexCount);
	~VertexBuffer();

	void Bind();
	void Unbind();

	inline unsigned int GetVertexCount() const { return m_VertexCount; };
};