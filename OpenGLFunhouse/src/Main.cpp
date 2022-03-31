#include "Renderer.h"

#include "Camera.h"

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <string>
#include <fstream>
#include <sstream>

Camera camera;

std::pair<int, int> getWindowSize()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	int xpos, ypos, width, height;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);

	return std::make_pair(width / 2, width * 3/8);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	camera.MouseCallback(xpos, ypos);
}

void processInput(GLFWwindow* window, Camera& camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.MoveForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.MoveBackward();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.MoveRight();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.MoveLeft();

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.Tilt(-1.0f);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.Tilt(1.0f);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.Turn(1.0f);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.Turn(-1.0f);
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

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

		// MVP Matrices
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(windowSize.first / windowSize.second), 0.1f, 100.0f);

		

		// Renderer initialization
		Renderer renderer;

		// Main variables


		float krtkus1[] = { 0.0f, 0.0f, 0.0f };

		float rotation1[] = { 0.0f, 0.0f, 0.0f };

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
				model = glm::rotate(model, glm::radians(rotation1[0]), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, glm::radians(rotation1[1]), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(rotation1[2]), glm::vec3(0.0f, 0.0f, 1.0f));

				glm::mat4 view = camera.GenViewMat();

				glm::mat4 mvp = proj * view * model;
				shader.UniformMat4f("u_MVP", mvp);
			}

			renderer.Draw(va, ib, shader, texture);

			/*{
				ImGui::SliderFloat3("krtkus 1", krtkus1, -1.0f, 1.0f);
				ImGui::SliderFloat3("rotation 1", rotation1, -180, 180);

				if (ImGui::Button("<-"))
					camera.Turn(-1.0f);
				ImGui::SameLine();
				if (ImGui::Button("->"))
					camera.Turn(1.0f);
			}*/

			glfwPollEvents();
			processInput(window, camera);

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