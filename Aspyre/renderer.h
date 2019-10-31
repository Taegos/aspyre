#include "GL/glew.h"
#include "glm/vec2.hpp"
#include "texture.h"
#include "shader.h"
#include <string>
#include <vector>

struct RenderJob {
	int texture;
	glm::ivec2 top_left{ 0, 0 };
	unsigned int width{ 0 };
	unsigned int height{ 0 };
};

class Renderer {
public:
	Renderer();
	void flush();
	void add_job(RenderJob&&);
	int load_texture(const std::string&);
private:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	std::vector<Texture> textures;
	std::vector<RenderJob> jobs;
};
