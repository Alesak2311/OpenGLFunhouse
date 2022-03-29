#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCall(x) ClearError(); x; ASSERT(CheckError())

void ClearError();

bool CheckError();