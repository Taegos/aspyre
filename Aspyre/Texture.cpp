#include "texture.h"
#include "exceptions.h"
#include <vector>
#include "lodepng.h"

using namespace std;

Texture::Texture(const std::string& file_name)
{
	unsigned int width;
	unsigned int height;
	vector<unsigned char> image;
	unsigned int error = lodepng::decode(image, width, height, file_name.c_str());
	if (error) {
		throw IOException(lodepng_error_text(error));
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::bind(unsigned int unit)
{
	if (unit < 0 || unit > 31) {
		throw OpenGLException("Texture unit have to be in range 0 - 31");
	}
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}
