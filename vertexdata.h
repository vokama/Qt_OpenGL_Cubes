#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>
#include <QVector2D>

class VertexData
{
public:
    VertexData()
    {}

    VertexData(QVector3D p, QVector4D c)
        : position(p), colour(c)
    {}

    ~VertexData()
    {}

    QVector3D position;
    QVector4D colour;
};

#endif // VERTEXDATA_H
