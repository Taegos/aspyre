#include "keyboard_emitter.h"
#include <iostream>
using namespace std;

InputData KeyboardEmitter::on_key_down(unsigned int key, std::function<void()> cb)
{
	keys_down[key].push_back(cb);
	return { key, Action::DOWN, keys_down[key].size() - 1 };
}


InputData KeyboardEmitter::on_key_held(unsigned int key, std::function<void()> cb)
{
	keys_held[key].push_back(cb);
	return { key, Action::HELD, keys_held[key].size() - 1 };
}


InputData KeyboardEmitter::on_key_up(unsigned int key, std::function<void()> cb)
{
	keys_up[key].push_back(cb);
	return { key, Action::UP, keys_up[key].size() - 1 };
}

void KeyboardEmitter::emit_held()
{
	for (int key : is_key_held) {   
		emit_key(key, keys_held);
	}
}

void KeyboardEmitter::unregister(InputData data)
{
	KeyRegistry* registry = keys_down;
	switch (data.action) {
	case Action::HELD:
		registry = keys_held;
		break;
	case Action::UP:
		registry = keys_up;
		break;
	}
	registry[data.code][data.index] = NULL;
}

void KeyboardEmitter::key_callback(int key, int scancode, int action, int mods)
{
	if (action == GLFW_REPEAT) {
		return;
	}
	if (action == GLFW_PRESS) {
		emit_key(key, keys_down);
		is_key_held.insert(key);
	}
	else if (action == GLFW_RELEASE) {
		emit_key(key, keys_up);
		is_key_held.erase(key);
	}
}


void KeyboardEmitter::emit_key(int key, KeyRegistry* registry)
{
	if (registry[key].size() > 0) {
		for (auto cb : registry[key]) {
			if (cb != NULL) {

				cb();
			}
		}
	}
}