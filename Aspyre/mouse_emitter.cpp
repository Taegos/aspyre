#include "mouse_emitter.h"

MouseEmitter::MouseEmitter(GLFWwindow* window) : window {window}
{	

}

void MouseEmitter::mouse_callback(int button, int action, int mods)
{
	if (action == GLFW_REPEAT) {
		return;
	}
	if (action == GLFW_PRESS) {
		emit_button(button, buttons_down);
		is_button_held.insert(button);
	}
	else if (action == GLFW_RELEASE) {
		emit_button(button, buttons_up);
		is_button_held.erase(button);
	}
}

InputData MouseEmitter::on_button_down(unsigned int button, std::function<void(glm::vec2)> cb)
{
	buttons_down[button].push_back(cb);
	return { button, Action::DOWN, buttons_down[button].size() - 1 };
}

InputData MouseEmitter::on_button_held(unsigned int button, std::function<void(glm::vec2)> cb)
{
	buttons_held[button].push_back(cb);
	return { button, Action::HELD, buttons_held[button].size() - 1 };
}

InputData MouseEmitter::on_button_up(unsigned int button, std::function<void(glm::vec2)> cb)
{
	buttons_up[button].push_back(cb);
	return { button, Action::UP, buttons_up[button].size() - 1 };
}

void MouseEmitter::emit_held()
{
	for (int button : is_button_held) {
		emit_button(button, buttons_held);
	}
}

void MouseEmitter::unregister(InputData data)
{
	MouseRegistry* registry = buttons_down;
	switch (data.action) {
	case Action::HELD:
		registry = buttons_held;
		break;
	case Action::UP:
		registry = buttons_up;
		break;
	}
	registry[data.code][data.index] = NULL;
}

void MouseEmitter::emit_button(int button, MouseRegistry *registry)
{
	if (registry[button].size() > 0) {
		for (auto cb : registry[button]) {
			if (cb != NULL) {
				double x;
				double y;
				glfwGetCursorPos(window, &x, &y);
				cb({ x, y });
			}
		}
	}
}
