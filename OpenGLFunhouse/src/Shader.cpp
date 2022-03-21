#include "Shader.h"

#include <iostream>

Shader::Shader(std::string filepath)
	: m_ID(0), m_Filepath(filepath)
{
	ShaderSources source = ParseShader();

	m_ID = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, source.vsSource);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, source.fsSource);

	GLCall(glAttachShader(m_ID, fs));
	GLCall(glAttachShader(m_ID, vs));
	GLCall(glLinkProgram(m_ID));
	GLCall(glValidateProgram(m_ID));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
}

Shader::~Shader()
{

}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_ID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

ShaderSources Shader::ParseShader() const
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	std::ifstream stream(m_Filepath);
	std::string line;
	std::stringstream ss[2];

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CompileShader(GLuint type, const std::string& source) const
{
	GLCall(GLuint shaderId = glCreateShader(type));
	const GLchar* src = source.c_str();
	GLCall(glShaderSource(shaderId, 1, &src, nullptr));
	GLCall(glCompileShader(shaderId));

	int result;
	GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(shaderId, length, &length, message));

		std::cout << message << std::endl;
	}

	return shaderId;
}