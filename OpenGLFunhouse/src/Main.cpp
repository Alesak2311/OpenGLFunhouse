#include "Renderer.h"

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

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
		glEnable(GL_DEPTH_TEST);

		// Texture creation
		Texture texture("res/textures/krtkus.png");
		texture.Bind();

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Vertex Array creation
		VertexArray va;

		// Vertex Layout creation
		VertexLayout layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 2);

		// Vertex Buffer creation
		/*   positions				texture coords */
		float positions[] = {
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,

			 0.5f, -0.5f, 1.0f,		1.0f, 0.0f,
			-0.5f,  0.5f, 1.0f,		0.0f, 1.0f,
			-0.5f, -0.5f, 1.0f,		0.0f, 0.0f,
			 0.5f,  0.5f, 1.0f,		1.0f, 1.0f
		};

		VertexBuffer vb(positions, layout, 8);

		// Bind Vertex Buffer and Layout to Vertex Array
		va.AddBuffer(vb, layout);

		// Index Buffer creation
		unsigned int indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		IndexBuffer ib(indices, 6);

		// MVP Matrices
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(windowSize.first / windowSize.second), 0.1f, 100.0f);

		

		// Renderer initialization
		Renderer renderer;

		// Main variables

		float camera[] = { 0.0f, 0.0f, -1.0f };

		float krtkus1[] = { 0.0f, 0.0f, 0.0f };

		float rotation[] = { 0.0f, 0.0f, 0.0f };

		// Main loop
		while (!glfwWindowShouldClose(window))
		{
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			renderer.Clear();

			shader.Uniform1i("u_Texture", 0);

			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(krtkus1[0], krtkus1[1], krtkus1[2]));
				model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));

				glm::mat4 view = glm::mat4(1.0f);
				view = glm::translate(view, glm::vec3(camera[0], camera[1], camera[2]));

				glm::mat4 mvp = proj * view * model;
				shader.UniformMat4f("u_MVP", mvp);
			}

			renderer.Draw(va, ib, shader, texture);

			{
				ImGui::SliderFloat3("camera", camera, -3.0f, 3.0f);
				ImGui::SliderFloat3("krtkus 1", krtkus1, -1.0f, 1.0f);
				ImGui::SliderFloat3("rotation", rotation, -180, 180);
			}

			glfwPollEvents();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
		}
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}