#include "window.h"
#include "exceptions.h"

using namespace std;

Window::Window(int width, int height, const string& title) :
	window { init_window(width, height, title) },
	mouse_emitter { window }
{
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::closed()
{
    return glfwWindowShouldClose(window);
}

InputID Window::on_key_down(int key, std::function<void()> cb)
{
	InputData data = keyboard_emitter.on_key_down(key, cb);
	return { InputType::KEYBOARD, data };
}

InputID Window::on_key_held(int key, std::function<void()> cb)
{
	InputData data = keyboard_emitter.on_key_held(key, cb);
	return { InputType::KEYBOARD, data };
}

InputID Window::on_key_up(int key, std::function<void()> cb)
{
	InputData data = keyboard_emitter.on_key_up(key, cb);
	return { InputType::KEYBOARD, data };
}

InputID Window::on_mouse_down(int button, std::function<void(glm::vec2)> cb)
{
	InputData data = mouse_emitter.on_button_down(button, cb);
	return { InputType::MOUSE, data };
}

InputID Window::on_mouse_held(int button, std::function<void(glm::vec2)> cb)
{
	InputData data = mouse_emitter.on_button_held(button, cb);
	return { InputType::MOUSE, data };
}

InputID Window::on_mouse_up(int button, std::function<void(glm::vec2)> cb)
{
	InputData data = mouse_emitter.on_button_up(button, cb);
	return { InputType::MOUSE, data };
}

void Window::unregister(InputID id)
{
	switch (id.type)
	{
	case InputType::KEYBOARD:
		keyboard_emitter.unregister(id.data);
		break;
	case InputType::MOUSE:
		mouse_emitter.unregister(id.data);
		break;
	}
}

GLFWwindow* Window::init_window(int width, int height, const string &title)
{
	if (!glfwInit()) {
		throw OpenGLException("GLFW failed to initialize");
	}
	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw OpenGLException("failed to create window");
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	auto key_cb = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
		static_cast<Window*>(glfwGetWindowUserPointer(w))->key_callback(key, scancode, action, mods);
	};
	glfwSetKeyCallback(window, key_cb);

	auto mouse_cb = [](GLFWwindow* w, int button, int action, int mods) {
		static_cast<Window*>(glfwGetWindowUserPointer(w))->mouse_callback(button, action, mods);
	};
	glfwSetMouseButtonCallback(window, mouse_cb);
	return window;
}

void Window::key_callback(int key, int scancode, int action, int mods) {
	keyboard_emitter.key_callback(key, scancode, action, mods);
}

void Window::mouse_callback(int button, int action, int mods) {
	mouse_emitter.mouse_callback(button, action, mods);
}

void Window::update()
{
	keyboard_emitter.emit_held();
	mouse_emitter.emit_held();
    glfwSwapBuffers(window);
    glfwPollEvents();
}
