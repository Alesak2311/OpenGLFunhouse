#pragma once

#include "Tools.h"
#include <string>

class Texture
{
private:
	static GLuint s_BoundID;

	GLuint m_ID;
	std::string m_Filepath;
	unsigned char* m_Buffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(GLuint slot = 0);
	void Unbind();
};