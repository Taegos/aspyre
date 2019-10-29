#pragma once

enum class Action {
	DOWN,
	HELD,
	UP
};

struct InputData {
	unsigned int code;
	Action action;
	unsigned int index;
};