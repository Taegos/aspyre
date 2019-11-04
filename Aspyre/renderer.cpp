#include "renderer.h"
#include "exceptions.h"
#include "GL/glew.h"
#include "resources.h"

using namespace glm;

Renderer::Renderer()
{
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        throw OpenGLException("GLEW failed to initialize");
    }
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Renderer::flush()
{
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	
	glDrawElements(GL_TRIANGLES, call * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	call = 0;
}

void Renderer::push() 
{
	int vert_start = call * 8;
	
	//top right
	vertices[vert_start] = vec2(0.4f, 0.5f); //vertex 
	vertices[vert_start + 1] = vec2(1.0f, 1.0f); //texture c

	//bottom right
	vertices[vert_start + 2] = vec2(0.5f, -0.5f);
	vertices[vert_start + 3] = vec2(1.0f, 0.0f);

	//bottom left
	vertices[vert_start + 4] = vec2(-0.5f, -0.5f);
	vertices[vert_start + 5] = vec2(0.0f, 0.0f);

	//top left
	vertices[vert_start + 6] = vec2(-0.5f, 0.5f);
	vertices[vert_start + 7] = vec2(0.0f, 1.0f);

	//first triangle
	indices[call + 0] = call;
	indices[call + 1] = call + 1;
	indices[call + 2] = call + 3;

	//second triangle
	indices[call + 3] = call + 1;
	indices[call + 4] = call + 2;
	indices[call + 5] = call + 3;
	
	call++;
}

//https://learnopengl.com/Getting-started/Hello-Triangle
//https://gamedev.stackexchange.com/questions/10727/fastest-way-to-draw-quads-in-opengl-es
//https://github.com/jodem/glText-Android/blob/master/src/com/android/texample/SpriteBatch.java