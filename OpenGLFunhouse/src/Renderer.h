#pragma once

#include "Tools.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
};