#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLBuffer>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "vertexdata.h"

static const int cubeVertexCount = 8;

static const QVector3D cubeVertices[cubeVertexCount] =
                                        {QVector3D(-1, 1, 1),  // front plane
                                         QVector3D(1, 1, 1),
                                         QVector3D(1, -1, 1),
                                         QVector3D(-1, -1, 1),
                                         QVector3D(-1, 1, -1),  // back plane
                                         QVector3D(1, 1, -1),
                                         QVector3D(1, -1, -1),
                                         QVector3D(-1, -1, -1)};

static const GLubyte cubeIndices[] = {0, 2, 1, 0, 3, 2,   // front
                                      4, 3, 0, 4, 7, 3,   // left
                                      1, 6, 5, 1, 2, 6,   // right
                                      4, 1, 5, 4, 0, 1,   // top
                                      3, 6, 2, 3, 7, 6,   // bottom
                                      5, 7, 4, 5, 6, 7};  // back


struct CubeInstance
{
    QVector3D center;
    QMatrix4x4 rotation;
};

class Cube : QOpenGLFunctions_3_3_Core
{
public:
    Cube();
    ~Cube();

    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLBuffer m_instanceBuf;

    void addInstance(const CubeInstance& instance);
    void removeInstance(int idx);
    void selectInstance(int idx);

    void draw(const QMatrix4x4& viewProjectionMatrix);

private:
    void initShaders();

    QOpenGLShaderProgram m_program;
    std::vector<CubeInstance> m_instances;
    int m_instanceBufSize = 128 * sizeof(m_instances[0]);
    int m_highlightedInst;
};

#endif // CUBE_H
