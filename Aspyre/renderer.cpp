#include "renderer.h"
#include "exceptions.h"
#include "GL/glew.h"

Renderer::Renderer()
{
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        throw OpenGLException("GLEW failed to initialize");
    }
}

void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    //DRAW STUFF
}
