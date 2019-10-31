#include "resources.h"
#include "exceptions.h"
#include "lodepng.h"
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

const string Resources::path = "res\\";
const string Resources::shader_path = "shaders\\";
const string Resources::texture_path = "textures\\";

Texture Resources::load_texture(const std::string& name)
{
	unsigned int width;
	unsigned int height;
	vector<unsigned char> image;
	unsigned int error = lodepng::decode(image, width, height, name.c_str());
	if (error) {
		throw IOException(lodepng_error_text(error));
	}
	return Texture(name);
}

Shader Resources::load_shader(const std::string& name)
{
	std::string vert_file = read_file(shader_path + name + ".vs");
	std::string frag_file = read_file(shader_path + name + ".fs");
	return Shader(vert_file, frag_file);
}

std::string Resources::read_file(const std::string& file_name)
{
	ifstream file(path + file_name);
	if (!file.is_open()) {
		throw IOException(path + file_name);
	}
	return string((istreambuf_iterator<char>(file)),
		istreambuf_iterator<char>());
}