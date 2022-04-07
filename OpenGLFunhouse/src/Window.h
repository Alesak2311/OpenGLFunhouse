#pragma once

#include "Camera.h"

#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;

	float m_Aspect;

	Camera* m_BoundCamera;

	double m_LastX;
	double m_LastY;
public:
	Window();
	~Window();

	inline void BindCamera(Camera* camera) { m_BoundCamera = camera; }
	inline void	UnbindCamera() { m_BoundCamera = nullptr; }

	void PollMouseOffset();
	void PollKeyboard();

	void PollEvents();

	inline GLFWwindow* GetGLFWWindow() const { return m_Window; }
	inline float GetAspectRatio() const { return m_Aspect; }
	inline Camera* GetBoundCamera() const { return m_BoundCamera; }
};

