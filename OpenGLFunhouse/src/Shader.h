#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"

struct ShaderSources
{
	std::string vsSource;
	std::string fsSource;
};

class Shader
{
private:
	GLuint m_ID;
	std::string m_Filepath;
public:
	Shader(std::string filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;
private:
	ShaderSources ParseShader() const;
	GLuint CompileShader(GLuint type, const std::string& source) const;
};