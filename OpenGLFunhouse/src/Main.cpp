#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "Shader.h"

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

	Shader shader("res/shader/Basic.shader");
	shader.Bind();

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