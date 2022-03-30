#pragma once

#include "Tools.h"

class Camera
{
private:
	const static float s_Speed;

	glm::vec3 m_Pos;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
public:
	Camera();
	~Camera();

	inline glm::mat4 GenViewMat() const { return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up); }

	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
};