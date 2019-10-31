#include "renderer.h"
#include "exceptions.h"
#include "GL/glew.h"
#include "resources.h"

Renderer::Renderer()
{
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        throw OpenGLException("GLEW failed to initialize");
    }

	float verts[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Renderer::flush()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::add_job(RenderJob&& job)
{
	jobs.push_back(job);
}

int Renderer::load_texture(const std::string& path)
{
	textures.push_back(Texture{ path });
	return textures.size() - 1;
}
//https://learnopengl.com/Getting-started/Hello-Triangle
//https://gamedev.stackexchange.com/questions/10727/fastest-way-to-draw-quads-in-opengl-es
//https://github.com/jodem/glText-Android/blob/master/src/com/android/texample/SpriteBatch.java