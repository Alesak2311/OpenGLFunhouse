#pragma once

#include "Tools.h"

#include <vector>

struct VertexLayoutElement
{
	GLuint type;
	unsigned int count;
	GLuint normalized;

	unsigned int size;

	VertexLayoutElement(GLuint type, unsigned int count, GLuint normalized);
};

class VertexLayout
{
private:
	std::vector<VertexLayoutElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexLayout();

	void Push(GLuint type, unsigned int count, GLuint normalized = GL_FALSE);

	inline const unsigned int& GetStride() const { return m_Stride; };
	inline const std::vector<VertexLayoutElement>& GetElements() const { return m_Elements; };
};