#pragma once

#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) ClearError(); x; ASSERT(CheckError())

void ClearError();

bool CheckError();