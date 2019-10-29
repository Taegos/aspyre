#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"
#include <GL/glew.h>

class Vertex {
 public:
 Vertex(const glm::vec3 & pos) :
    pos { pos } {}
 private:
    glm::vec3 pos;
};

class Mesh {

 public:
    Mesh(Vertex*, unsigned int);
    ~Mesh();
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
