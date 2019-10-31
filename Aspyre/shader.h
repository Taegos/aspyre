#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
 public:
    Shader(const std::string &, const std::string &);
    ~Shader();
    void use();
 private:
    GLuint create_shader(const std::string &, GLenum);
    void validate_shader(GLint, GLenum);
    void validate_program(GLint, GLenum);
    static const unsigned int NUM_SHADERS = 2;
    GLuint program;
    GLuint shaders[NUM_SHADERS];
};

#endif // SHADER_H
