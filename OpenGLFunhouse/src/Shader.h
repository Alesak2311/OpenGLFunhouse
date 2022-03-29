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

	void Uniform1i(const std::string& name, int v0);
	void Uniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void UniformMat4f(const std::string& name, const glm::mat4& mat);

	inline GLuint GetID() const { return m_ID; };
private:
	ShaderSources ParseShader() const;
	GLuint CompileShader(GLuint type, const std::string& source) const;
};