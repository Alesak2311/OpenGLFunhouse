#pragma once

#include "Renderer.h"

class IndexBuffer
{
private:
	GLuint m_ID;
	unsigned int m_IndexCount;
public:
	IndexBuffer(const void* data, unsigned int indexCount);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetIndexCount() const { return m_IndexCount; };
};