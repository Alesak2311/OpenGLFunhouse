#pragma once

#include "Tools.h"

#include <GLFW/glfw3.h>
#include <utility>

class Camera
{
private:
	const static float s_Speed;
	static float s_Sensitivity;

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

	inline void MoveForward() { m_Pos += s_Speed * m_Front; }
	inline void MoveBackward() { m_Pos -= s_Speed * m_Front; }
	inline void MoveRight() { m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * s_Speed; }
	inline void MoveLeft() { m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * s_Speed; }

	void Turn(float angle);
	void Tilt(float angle);

	void HandleMouse(double xOffset, double yOffset);
};