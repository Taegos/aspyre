#include "texture.h"
#include "exceptions.h"
#include <vector>
#include "lodepng.h"

using namespace std;
int Texture::id = 0;

#include <iostream>
Texture::Texture(unsigned int width, unsigned int height, vector<unsigned char> image)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	Texture::id++;
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::bind()
{
//	if (unit < 0 || unit > 31) {
	//	throw OpenGLException("Texture unit have to be in range 0 - 31");
//	}
	glActiveTexture(GL_TEXTURE0 + Texture::id);
	glBindTexture(GL_TEXTURE_2D, texture);
}
