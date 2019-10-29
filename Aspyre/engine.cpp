#include "engine.h"
#include "window.h"
#include "renderer.h"
#include <iostream>

using namespace std;

void Engine::run(int width, int height, const string& title) {
	Window window{ 1000, 1000, "title" };
	Renderer renderer;
    InputID id0 = window.on_key_down(
		GLFW_KEY_SPACE,
		[]() { cout << "SPACE DOWN" << endl; }
	);

	InputID id1 = window.on_key_held(
		GLFW_KEY_SPACE,
		[]() { cout << "SPACE HELD" << endl; }
	);

	window.on_key_up(
		GLFW_KEY_SPACE,
		[]() { cout << "SPACE UP" << endl; }
	);

	window.on_key_down(
		GLFW_KEY_D,
		[&]() {
			cout << "DEL" << endl;
			window.unregister(id0);
			window.unregister(id1);
			window.on_key_held(
				GLFW_KEY_F,
				[]() {cout << "F HELD" << endl; }
			);
		}
	);

	window.on_mouse_down(
		GLFW_MOUSE_BUTTON_LEFT,
		[](glm::vec2 p) {
			cout << "LEFT MOUSE DOWN: " << p.x << " : " << p.y << endl;
		}
	);
	
	window.on_mouse_held(
		GLFW_MOUSE_BUTTON_LEFT,
		[](glm::vec2 p) {
			cout << "LEFT MOUSE HELD: " << p.x << " : " << p.y << endl;
		}
	);

	window.on_mouse_up(
		GLFW_MOUSE_BUTTON_LEFT,
		[](glm::vec2 p) {
			cout << "LEFT MOUSE UP: " << p.x << " : " << p.y << endl;
		}
	);

	window.on_mouse_held(
		GLFW_MOUSE_BUTTON_RIGHT,
		[](glm::vec2 p) {
			cout << "RIGHT MOUSE HELD: " << p.x << " : " << p.y << endl;
		}
	);

    while (!window.closed()) {
        renderer.draw();
        window.update();
    }
}
