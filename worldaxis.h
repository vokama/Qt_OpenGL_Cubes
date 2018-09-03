#ifndef WORLDAXIS_H
#define WORLDAXIS_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "vertexdata.h"

class WorldAxis : QOpenGLFunctions_3_3_Core
{
public:
    WorldAxis();
    ~WorldAxis();

    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

    void draw(const QMatrix4x4& viewProjectionMatrix);

private:
    QOpenGLShaderProgram m_program;
    std::vector<VertexData> m_vertices;
    std::vector<GLubyte> m_indices;

    void initShaders();
};

#endif // WORLDAXIS_H
