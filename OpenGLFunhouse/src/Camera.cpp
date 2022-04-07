#include "Camera.h"

const float Camera::s_Speed = 0.05f;
float Camera::s_Sensitivity = 0.1f;

Camera::Camera()
	:m_Pos(glm::vec3(0.0f, 0.0f, 3.0f)),
	m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_yaw(-90.0f), m_pitch(0.0f)
{
	CalculateDirection();
}

Camera::~Camera()
{
}

void Camera::CalculateDirection()
{
	m_Front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_Front.y = sin(glm::radians(m_pitch));
	m_Front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
}

void Camera::Turn(float angle)
{
	m_yaw += angle;

	CalculateDirection();
}

void Camera::Tilt(float angle)
{
	m_pitch += angle;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	CalculateDirection();
}

void Camera::HandleMouse(double xOffset, double yOffset)
{
	xOffset *= s_Sensitivity;
	yOffset *= s_Sensitivity;

	Turn((float)(xOffset));
	Tilt((float)(yOffset));
}