#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

ShaderSource ParseShader(const std::string filepath)
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	std::ifstream stream(filepath);
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

GLuint CompileShader(GLuint type, const std::string& source)
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

GLuint CreateShader(std::string filepath)
{
	ShaderSource source = ParseShader(filepath);

	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

	GLCall(glAttachShader(program, fs));
	GLCall(glAttachShader(program, vs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

int main()
{
	if (!glfwInit())
	{
		glfwTerminate();
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1600, 1200, "OpenGLFunhouse", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	GLuint shader = CreateShader("res/shader/Basic.shader");
	GLCall(glUseProgram(shader));

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};

	GLuint vb;
	GLCall(glGenBuffers(1, &vb));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		GLCall(glfwSwapBuffers(window));
		GLCall(glfwPollEvents());
	}

	GLCall(glDeleteBuffers(1, &vb));
	glfwTerminate();
}