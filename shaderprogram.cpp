#include "shaderprogram.h"

#include <iostream>

ShaderProgram::ShaderProgram()
{
    if(!addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.vert")) {
        std::cout << "Vertex shader compilation failed" << log().toStdString() << "\n";
        exit(EXIT_FAILURE);
    }

    if(!addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.frag")) {
        std::cout << "Fragment shader compilation failed" << log().toStdString() << "\n";
        exit(EXIT_FAILURE);
    }

    if(!link()) {
        std::cout << "Shader program linking failed" << log().toStdString() << "\n";
        exit(EXIT_FAILURE);
    }
}
