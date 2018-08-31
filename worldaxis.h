#ifndef WORLDAXIS_H
#define WORLDAXIS_H

#include <QOpenGLBuffer>

#include "vertexdata.h"

class WorldAxis
{
public:
    WorldAxis();
    ~WorldAxis();

    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

    void draw();
};

#endif // WORLDAXIS_H
