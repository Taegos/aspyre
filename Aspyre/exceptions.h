#include <string>
#include <iostream>
#include <exception>

class DebugException : public std::exception
{
 public:
 DebugException(const std::string & message)
     : message {message}
    {
        std::cerr << message << std::endl;
    }

    const char * what() const throw()
    {
        return message.c_str();
    }
 private:
    const std::string & message;
};

class IOException : public DebugException
{
 public:
 IOException(const std::string & file_name)
     : DebugException("IOError: failed to open file \"" + file_name + "\".") {}
};

class OpenGLException : public DebugException
{
 public:
 OpenGLException(const std::string & message)
     : DebugException("OpenGLError: " + message + ".") {}
};

class GLFWException : public DebugException
{
 public:
 GLFWException(const std::string & message)
     : DebugException("GLFWError: " + message + ".") {}
};
