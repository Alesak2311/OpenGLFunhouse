#pragma once

#include "Tools.h"

#include <string>

struct ShaderSources
{
	std::string vsSource;
	std::string fsSource;
};

class Shader
{
private:
	static GLuint s_BoundID;

	GLuint m_ID;
	std::string m_Filepath;
public:
	Shader(std::string filepath);
	~Shader();

	void Bind();
	void Unbind();

	void Uniform4f(float v0, float v1, float v2, float v3);

	inline GLuint GetID() const { return m_ID; };
private:
	ShaderSources ParseShader() const;
	GLuint CompileShader(GLuint type, const std::string& source) const;
};