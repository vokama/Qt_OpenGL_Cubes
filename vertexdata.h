#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>
#include <QVector2D>

class VertexData
{
public:
    VertexData()
    {}

    VertexData(QVector3D p)
        : position(p)
    {}

    ~VertexData()
    {}

    QVector3D position;
};

#endif // VERTEXDATA_H
