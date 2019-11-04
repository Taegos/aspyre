#include "shader.h"
#include "texture.h"
#include "engine.h"
#include "window.h"
#include "renderer.h"
#include "resources.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>"

using namespace std;
using namespace glm;

void Engine::run(int width, int height, const string& title) {
	
	Window window{ width, height, "title" };
	Renderer renderer;
	Shader shader0 = Resources::load_shader("shader");
	Shader shader1 = Resources::load_shader("shader");
	Texture texture0 = Resources::load_texture("fatstronaut.png");
	Texture texture1 = Resources::load_texture("fatstronaut.png");
	vec3 pos(0.0f, 0.0f, 0.0f);
	window.on_key_held(
		GLFW_KEY_A,
		[&]() { pos.x -= 0.01f; }
	);
	window.on_key_held(
		GLFW_KEY_W,
		[&]() { pos.y += 0.01f; }
	);
	window.on_key_held(
		GLFW_KEY_D,
		[&]() { pos.x += 0.01f; }
	);
	window.on_key_held(
		GLFW_KEY_S,
		[&]() { pos.y -= 0.01f; }
	);

	Renderer renderer1;
    while (!window.closed()) {
		glClearColor(94.0f / 255, 102.0f / 255, 112.0f / 255, 255);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.push();
		texture0.bind();
		shader0.use();

		mat4 view = mat4(1.0f);
		mat4 model = mat4(1.0f);

		float size = .01f;
		float right = width / 2 * size;
		float top = -height / 2 * size;

		glm::mat4 projection = glm::ortho(
			-right,
			right,
			-top,
			top,
			0.0f,
			100.0f
		);
		   		
		//model = glm::scale(model, glm::vec3(100.0f, 100.0f, 0.0f));
		model = glm::translate(model, pos);
		view = glm::translate(view, vec3(20.0f, 1.0f, 0.0f));
		shader0.set_mat4("projection", projection); 
		shader0.set_mat4("view", view);
		shader0.set_mat4("model", model);

		
		renderer.flush();
        
		renderer1.push();
		texture1.bind();
		model = glm::translate(model, vec3(0, 0, 0));
		shader0.set_mat4("model", model);
		shader0.use();
		renderer1.flush();

		window.update();


    }
}
