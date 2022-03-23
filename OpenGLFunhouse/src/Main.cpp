#include "Renderer.h"

#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>


std::pair<int, int> getWindowSize()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	int xpos, ypos, width, height;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);

	return std::make_pair(width / 2, width * 3/8);
}

int main()
{
	// Setup
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

	glfwSwapInterval(1);

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

		// Vertex Layout creation
		VertexLayout layout;
		layout.Push(GL_FLOAT, 2);

		// Vertex Buffer creation
		float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			-0.5f,  0.5f,
			 0.5f,  0.5f
		};

		VertexBuffer vb(positions, layout, 4);

		// Bind Vertex Buffer and Layout to Vertex Array
		va.AddBuffer(vb, layout);

		// Index Buffer creation
		unsigned int indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		IndexBuffer ib(indices, 6);

		// Renderer initialization
		Renderer renderer;

		// Main variables
		float r = 1.0f;
		float g = 1.0f;
		float b = 0.0f;
		float a = 1.0f;

		float increment = 0.01f;

		// Main loop
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			g -= increment;
			b += increment;

			if (g <= 0.0f || g >= 1.0f)
				increment *= -1;

			shader.Uniform4f(r, g, b, a);

			renderer.Draw(va, ib, shader);

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
}