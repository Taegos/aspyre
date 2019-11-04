#pragma once
#include <string>
#include <vector>
#include "GL/glew.h"

class Texture
{
public:
	Texture(unsigned int, unsigned int, std::vector<unsigned char>);
	~Texture();
	void bind();
	static int id;
private:
	GLuint texture;
};

