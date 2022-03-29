#include "Renderer.h"

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader, Texture& texture)
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	texture.Bind();
	shader.Uniform1i("u_Texture", 0);

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetIndexCount(), GL_UNSIGNED_INT, nullptr));
}
