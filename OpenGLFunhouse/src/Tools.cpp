#include "Tools.h"

#include <iostream>

void ClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool CheckError()
{
	if (GLenum error = glGetError())
	{
		std::cout << "[OPENGL ERROR] (" << error << ")" << std::endl;
		return false;
	}
	return true;
}