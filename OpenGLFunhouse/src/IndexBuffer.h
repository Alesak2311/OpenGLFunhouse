#pragma once

#include "Tools.h"

class IndexBuffer
{
private:
	static GLuint s_BoundID;

	GLuint m_ID;
	unsigned int m_IndexCount;
public:
	IndexBuffer(const void* data, unsigned int indexCount);
	~IndexBuffer();

	void Bind();
	void Unbind();

	inline unsigned int GetIndexCount() const { return m_IndexCount; };
};