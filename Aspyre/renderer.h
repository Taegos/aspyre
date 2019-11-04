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

const int MAX_DRAW_CALLS = 200;

class Renderer {
public:
	Renderer();
	void flush();
	void push();
private:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	
	int call = 0;
	glm::vec2 vertices[MAX_DRAW_CALLS * 8];
	int indices[MAX_DRAW_CALLS * 6];
};
