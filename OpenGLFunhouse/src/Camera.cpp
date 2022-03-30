#include "Camera.h"

const float Camera::s_Speed = 0.05f;

Camera::Camera()
	:m_Pos(glm::vec3(0.0f, 0.0f, 3.0f)), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Up(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

Camera::~Camera()
{
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
