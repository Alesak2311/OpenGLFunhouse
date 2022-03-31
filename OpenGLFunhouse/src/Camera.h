#pragma once

#include "Tools.h"

#include <GLFW/glfw3.h>

class Camera
{
private:
	const static float s_Speed;
	static bool s_FirstMouse;
	static float s_Sensitivity;

	float m_LastX, m_LastY;

	glm::vec3 m_Pos;
	glm::vec3 m_Front;
	glm::vec3 m_Up;

	float m_yaw;
	float m_pitch;

	void CalculateDirection();

public:
	Camera();
	~Camera();

	inline glm::mat4 GenViewMat() const { return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up); }

	void MouseCallback(double xpos, double ypos);

	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();

	void Turn(float angle);
	void Tilt(float angle);
};