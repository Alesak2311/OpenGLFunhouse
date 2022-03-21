#pragma once
#include <GL/glew.h>
#include <iostream>

#define GLCall(x) ClearError(); x; CheckError()

void ClearError();

void CheckError();