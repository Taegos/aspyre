#include "quad.h"

Quad::Quad(glm::vec2 top_left, float width, float height)
{
   glGenVertexArrays(1, &vertex_arr_obj);
    glBindVertexArray(vertex_arr_obj);

    glGenBuffers(1, &vertex_arr_obj);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_arr_buffers[POSITION_VB]);

    glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glBindVertexArray(0);

}

Quad::~Quad()
{
    glDeleteVertexArrays(1, &vertex_arr_obj);
}

void Quad::draw()
{
    glBindVertexArray(vertex_arr_obj);

    glDrawArrays(GL_TRIANGLES, 0, draw_count);

    glBindVertexArray(0);
}
