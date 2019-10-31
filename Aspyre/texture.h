#pragma once
#include <string>
#include "GL/glew.h"

class Texture
{
public:
	Texture(const std::string &);
	~Texture();
	void bind(unsigned int);
private:
	GLuint texture;
};

