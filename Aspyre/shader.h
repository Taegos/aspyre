#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "glm/mat4x4.hpp"

class Shader {
 public:
    Shader(const std::string &, const std::string &);
    ~Shader();
    void use();
	void set_mat4(const std::string&, const glm::mat4&);
	GLuint program;
 private:
    GLuint create_shader(const std::string &, GLenum);
    void validate_shader(GLint, GLenum);
    void validate_program(GLint, GLenum);
  
};

#endif // SHADER_H
