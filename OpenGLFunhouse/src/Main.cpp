#include "Renderer.h"

#include "Camera.h"

#include "Window.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <string>
#include <fstream>
#include <sstream>

int main()
{
	// Setup
	Window window;
	Camera camera;

	window.BindCamera(&camera);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window.GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Initialize GLEW
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
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,   // 0
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,   // 1
			 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,   // 2
			-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,   // 3
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,   // 4
			 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,   // 5
			 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,   // 6
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,   // 7
			-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,   // 8
			-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,   // 9
			-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,   // 10
			 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,   // 11
			 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,   // 12
			 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,   // 13
			 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,   // 14
			-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,   // 15
		};

		VertexBuffer vb(positions, layout, 16);

		// Bind Vertex Buffer and Layout to Vertex Array
		va.AddBuffer(vb, layout);

		// Index Buffer creation
		unsigned int indices[] = {
			0 , 1 , 2 ,
			2 , 3 , 0 ,

			4 , 5 , 6 ,
			6 , 7 , 4 ,

			8 , 9 , 10,
			10, 4 , 8 ,

			11, 2 , 12,
			12, 13, 11,

			10, 14, 5 ,
			5 , 4 , 10,

			3 , 2 , 11,
			11, 15, 3
		};

		IndexBuffer ib(indices, 36);

		// Projection Matrix
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), window.GetAspectRatio(), 0.1f, 100.0f);		

		// Renderer initialization
		Renderer renderer;

		// Main variables

		// Main loop
		while (!glfwWindowShouldClose(window.GetGLFWWindow()))
		{
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			renderer.Clear();

			shader.Uniform1i("u_Texture", 0);

			{
				glm::mat4 model = glm::mat4(1.0f);

				glm::mat4 view = window.GetBoundCamera()->GenViewMat();

				glm::mat4 mvp = proj * view * model;
				shader.UniformMat4f("u_MVP", mvp);
			}

			renderer.Draw(va, ib, shader, texture);

			window.PollEvents();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window.GetGLFWWindow());
		}
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}