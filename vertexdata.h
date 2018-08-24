#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>
#include <QVector2D>

class VertexData
{
public:
    VertexData()
    {}

    VertexData(QVector3D p, QVector2D t)
        : position(p), texCoord(t)
    {}

    ~VertexData()
    {}

    QVector3D position;
    QVector2D texCoord;
};

#endif // VERTEXDATA_H
