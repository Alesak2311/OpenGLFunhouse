#include "Renderer.h"

void ClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

void CheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OPENGL ERROR] (" << error << ")" << std::endl;
	}
}