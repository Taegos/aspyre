#pragma once
#include "glm/glm.hpp"

class Camera
{
public:
	Camera(float, float, float, float);
	~Camera();
	void set_pos(const glm::vec3);
private:
	glm::mat4 projection;
	glm::mat4 view;
};

