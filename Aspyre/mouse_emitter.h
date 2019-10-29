#pragma once
#include "input_data.h"
#include "glm/vec2.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <set>
#include <vector>

typedef std::vector<std::function<void(glm::vec2)>> MouseRegistry;

class MouseEmitter
{
public:
	MouseEmitter(GLFWwindow*);
	InputData on_button_down(unsigned int, std::function<void(glm::vec2) > );
	InputData on_button_held(unsigned int, std::function<void(glm::vec2)>);
	InputData on_button_up(unsigned int, std::function<void(glm::vec2)>);
	void emit_held();
	void unregister(InputData);
	void mouse_callback(int, int, int);
private:
	void emit_button(int, MouseRegistry*);
	GLFWwindow* window;
	std::set<int> is_button_held;
	MouseRegistry buttons_down[GLFW_MOUSE_BUTTON_LAST];
	MouseRegistry buttons_held[GLFW_MOUSE_BUTTON_LAST];
	MouseRegistry buttons_up[GLFW_MOUSE_BUTTON_LAST];
};