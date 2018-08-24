#ifndef WORLDAXIS_H
#define WORLDAXIS_H

#include <QOpenGLBuffer>

#include "vertexdata.h"

class WorldAxis
{
public:
    WorldAxis();

    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

private:
    void initGraphics();
};

#endif // WORLDAXIS_H
