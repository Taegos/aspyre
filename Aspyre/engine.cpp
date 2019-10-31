#include "shader.h"
#include "texture.h"
#include "engine.h"
#include "window.h"
#include "renderer.h"
#include "resources.h"
#include <iostream>

using namespace std;

void Engine::run(int width, int height, const string& title) {
	Window window{ 1000, 1000, "title" };
	Renderer renderer;
	Shader shader = Resources::load_shader("shader");

    while (!window.closed()) {
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		renderer.flush();
        window.update();
    }
}
