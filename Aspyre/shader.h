#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
 public:
    Shader(const std::string &);
    ~Shader();
    void bind();
 private:
    const std::string path = "res\\shaders\\";

    std::string read_shader_file(const std::string &);
    GLuint create_shader(const std::string &, GLenum);
    void check_error(GLuint, GLenum, bool);
    void validate_shader(GLint, GLenum);
    void validate_program(GLint, GLenum);
    static const unsigned int NUM_SHADERS = 2;
    GLuint program;
    GLuint shaders[NUM_SHADERS];
};

#endif // SHADER_H
