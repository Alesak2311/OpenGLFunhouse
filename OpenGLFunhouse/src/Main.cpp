#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"

std::pair<int, int> getWindowSize()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	int xpos, ypos, width, height;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);

	return std::make_pair(width / 2, width * 3/8);
}

int main()
{
	if (!glfwInit())
	{
		glfwTerminate();
		return -1;
	}

	std::pair<int, int> windowSize = getWindowSize();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowSize.first, windowSize.second, "OpenGLFunhouse", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	// GL object scope
	{
		// Shader creation
		Shader shader("res/shader/Basic.shader");
		shader.Bind();

		// Vertex Array creation
		VertexArray va;

		// Vertex Buffer creation
		float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			-0.5f,  0.5f,

			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};
		VertexBuffer vb(positions, 6 * 2 * sizeof(float));

		// Vertex Layout creation
		VertexLayout layout;
		layout.Push(GL_FLOAT, 2);

		va.AddBuffer(vb, layout);

		// TODO: Index Buffer creation

		// Main loop
		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}
	}
	glfwTerminate();
}