#pragma once

#include "glad/gl.h"

namespace unify::graphics {


    class OpenGLRenderer {
    public:
        OpenGLRenderer();
        ~OpenGLRenderer();
        void Draw();

        GLuint shaderProgram;

    private:
        GLuint VBO, VAO;
    };

}
