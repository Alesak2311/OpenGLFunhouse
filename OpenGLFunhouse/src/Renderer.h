#pragma once
#include <GL/glew.h>


#define GLCall(x) ClearError(); x; CheckError()

void ClearError();

void CheckError();