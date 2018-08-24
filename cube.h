#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLBuffer>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLTexture>

#include "vertexdata.h"

class Cube
{
public:
    Cube(QVector3D center = QVector3D(0, 0, 0), QVector3D rotation = QVector3D(0, 0, 0), float dimension = 1);
    ~Cube();

    void reset(QVector3D center = {0, 0, 0}, QVector3D rotation = {0, 0, 0});

    QOpenGLTexture *m_texture = nullptr;
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

private:
    void initGraphics();

    QVector3D m_center;
    QVector3D m_rotation;
    float m_dimension;
};

#endif // CUBE_H
