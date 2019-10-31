#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"
#include <GL/glew.h>

class Quad {

 public:
	Quad(glm::vec2, float, float);
    ~Quad();
    void draw();
 private:
    enum {
          POSITION_VB,
          NUM_BUFFERS
    };

    GLuint vertex_arr_obj;
    GLuint vertex_arr_buffers[NUM_BUFFERS];
    unsigned int draw_count;
};

#endif
