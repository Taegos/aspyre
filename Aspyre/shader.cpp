#include "shader.h"
#include "exceptions.h"
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;


Shader::Shader(const std::string & file_name)
{
    program = glCreateProgram();
    string vert_shader_file = read_shader_file(file_name + ".vs");
    string frag_shader_file = read_shader_file(file_name + ".fs");
    shaders[0] = create_shader(vert_shader_file, GL_VERTEX_SHADER);
    shaders[1] = create_shader(frag_shader_file, GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++) {
        glAttachShader(program, shaders[i]);
    }

    glBindAttribLocation(program, 0, "position");

    glLinkProgram(program);
    validate_program(program, GL_LINK_STATUS);
    validate_program(program, GL_VALIDATE_STATUS);

}


Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    glDeleteProgram(program);
}

void Shader::bind() {
    glUseProgram(program);
}

std::string Shader::read_shader_file(const std::string & file_name)
{
    ifstream file(file_name);
    if (!file.is_open()) {
        throw IOException(path + file_name);
    }
    return string((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
}

GLuint Shader::create_shader(const std::string & shader_file,
                             GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);

    if(shader == 0) {
        throw OpenGLException("Failed to create shader.");
    }

    const GLchar * shader_src_strings[1];
    GLint shader_src_strings_lengths[1];

    shader_src_strings[0] = shader_file.c_str();
    shader_src_strings_lengths[0] = shader_file.length();

    glShaderSource(shader, 1, shader_src_strings, shader_src_strings_lengths);
    glCompileShader(shader);

    validate_shader(shader, GL_COMPILE_STATUS);

    return shader;
}

void Shader::validate_shader(GLint shader, GLenum type)
{
    GLint success;
    glGetShaderiv(shader, type, &success);
    if (!success) {
        GLint log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        vector<GLchar> log(log_length);
        glGetShaderInfoLog(shader, log_length, &log_length, &log[0]);
        throw OpenGLException(string(log.begin(), log.end()));
    }
}

void Shader::validate_program(GLint shader, GLenum type)
{
    GLint success;
    glGetProgramiv(shader, type, &success);
    if (!success) {
        GLint log_length;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        vector<GLchar> log(log_length);
        glGetProgramInfoLog(shader, log_length, &log_length, &log[0]);
        throw OpenGLException(string(log.begin(), log.end()));
    }
}
