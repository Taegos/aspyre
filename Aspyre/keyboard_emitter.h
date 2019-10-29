#pragma once
#include "input_data.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <set>
#include <vector>

typedef std::vector<std::function<void()>> KeyRegistry;

class KeyboardEmitter
{
public:
	void emit_held();
	InputData on_key_down(unsigned int, std::function<void()>);
	InputData on_key_held(unsigned int, std::function<void()>);
	InputData on_key_up(unsigned int, std::function<void()>);
	void unregister(InputData);
	void key_callback(int, int, int, int);
private:
	void emit_key(int, KeyRegistry*);
	std::set<int> is_key_held;
	KeyRegistry keys_down[GLFW_KEY_LAST];
	KeyRegistry keys_held[GLFW_KEY_LAST];
	KeyRegistry keys_up[GLFW_KEY_LAST];
};

