#ifndef WINDOW_H
#define WINDOW_H

#include "keyboard_emitter.h"
#include "mouse_emitter.h"

enum class InputType {
	MOUSE,
	KEYBOARD
};

struct InputID
{
	InputType type;
	InputData data;
};

class Window
{
 public:
    Window(int, int, const std::string &);
    ~Window();
    void update();
    bool closed();

	InputID on_key_down(int, std::function<void()>);
	InputID on_key_held(int, std::function<void()>);
	InputID on_key_up(int, std::function<void()>);

	InputID on_mouse_down(int, std::function<void(glm::vec2)>);
	InputID on_mouse_held(int, std::function<void(glm::vec2)>);
	InputID on_mouse_up(int, std::function<void(glm::vec2)>);

	void unregister(InputID);
 private:
    void key_callback(int, int, int, int);
	void mouse_callback(int, int, int);
	GLFWwindow* init_window(int, int, const std::string &);
	GLFWwindow* window;

	KeyboardEmitter keyboard_emitter;
	MouseEmitter mouse_emitter;
};

#endif //WINDOW_HID
