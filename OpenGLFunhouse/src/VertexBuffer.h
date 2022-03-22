#pragma once

#include "Renderer.h"

#include "VertexLayout.h"

class VertexBuffer
{
private:
	GLuint m_ID;
	unsigned int m_VertexCount;
public:
	VertexBuffer(const void* data, const VertexLayout& layout, unsigned int vertexCount);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetVertexCount() const { return m_VertexCount; };
};