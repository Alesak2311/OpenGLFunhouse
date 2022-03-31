#include "Camera.h"

const float Camera::s_Speed = 0.05f;
bool Camera::s_FirstMouse = true;
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

void Camera::MouseCallback(double xpos, double ypos)
{
	if (s_FirstMouse)
	{
		m_LastX = xpos;
		m_LastY = ypos;
		s_FirstMouse = false;
	}

	float xoffset = xpos - m_LastX;
	float yoffset = m_LastY - ypos;
	m_LastX = xpos;
	m_LastY = ypos;

	xoffset *= s_Sensitivity;
	yoffset *= s_Sensitivity;

	Turn(xoffset);
	Tilt(yoffset);
}

void Camera::MoveForward()
{
	m_Pos += s_Speed * m_Front;
}

void Camera::MoveBackward()
{
	m_Pos -= s_Speed * m_Front;
}

void Camera::MoveRight()
{
	m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * s_Speed;
}

void Camera::MoveLeft()
{
	m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * s_Speed;
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
