#pragma once
#include <string>
#include "texture.h"
#include "shader.h"

class Resources
{
public:
	static Texture load_texture(const std::string&);
	static Shader load_shader(const std::string&);
private:
	static std::string read_file(const std::string&);

	static const std::string path;
	static const std::string texture_path;
	static const std::string shader_path;
};