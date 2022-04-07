#include "Window.h"

Window::Window()
	:m_BoundCamera(nullptr)
{
	// Initialize
	ASSERT(glfwInit());

	// Get window dimensions
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	int xpos, ypos, width, height;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
	width /= 2;
	height /= 2;

	m_Aspect = width / height;

	// Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	m_Window = glfwCreateWindow(width, height, "OpenGLFunhouse", NULL, NULL);
	glfwMakeContextCurrent(m_Window);

	glfwSwapInterval(1);

	// Setup mouse input
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(m_Window, &m_LastX, &m_LastY);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
}

void Window::PollMouseOffset()
{
	double xPos, yPos;
	glfwGetCursorPos(m_Window, &xPos, &yPos);

	double xOffset = xPos - m_LastX;
	double yOffset = m_LastY - yPos;

	m_LastX = xPos;
	m_LastY = yPos;

	if (m_BoundCamera)
		m_BoundCamera->HandleMouse(xOffset, yOffset);
}

void Window::PollKeyboard()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);

	if (m_BoundCamera)
	{
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			m_BoundCamera->MoveForward();
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			m_BoundCamera->MoveBackward();
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			m_BoundCamera->MoveRight();
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			m_BoundCamera->MoveLeft();

		if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS)
			m_BoundCamera->Tilt(-1.0f);
		if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
			m_BoundCamera->Tilt(1.0f);
		if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			m_BoundCamera->Turn(1.0f);
		if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS)
			m_BoundCamera->Turn(-1.0f);
	}
}

void Window::PollEvents()
{
	glfwPollEvents();
	PollMouseOffset();
	PollKeyboard();
}
