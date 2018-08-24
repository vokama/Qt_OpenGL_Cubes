#include "worldaxis.h"

#include <QVector>

WorldAxis::WorldAxis()
    : m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    m_arrayBuffer.create();
    m_arrayBuffer.bind();

    m_indexBuffer.create();
    m_indexBuffer.bind();

    initGraphics();
}

void WorldAxis::initGraphics()
{
    QVector<VertexData> vertices;
    QVector<GLuint> indices;

    float Width = 0.5f;
    float Length = 5.0f;

    float halfWidth = Width / 2.0f;

    // X Axis
    vertices.append(VertexData(QVector3D(0, halfWidth, halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(0, halfWidth, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(0, -halfWidth, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(0, -halfWidth, halfWidth), QVector2D()));

    vertices.append(VertexData(QVector3D(Length, halfWidth, halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(Length, halfWidth, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(Length, -halfWidth, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(Length, -halfWidth, halfWidth), QVector2D()));

    // Y Axis
    vertices.append(VertexData(QVector3D(-halfWidth, 0, halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(-halfWidth, 0, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(halfWidth, 0, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(halfWidth, 0, halfWidth), QVector2D()));

    vertices.append(VertexData(QVector3D(-halfWidth, Length, halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(-halfWidth, Length, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(halfWidth, Length, -halfWidth), QVector2D()));
    vertices.append(VertexData(QVector3D(halfWidth, Length, halfWidth), QVector2D()));

    // Z Axis
    vertices.append(VertexData(QVector3D(halfWidth, halfWidth, 0), QVector2D()));
    vertices.append(VertexData(QVector3D(-halfWidth, halfWidth, 0), QVector2D()));
    vertices.append(VertexData(QVector3D(-halfWidth, -halfWidth, 0), QVector2D()));
    vertices.append(VertexData(QVector3D(halfWidth, -halfWidth, 0), QVector2D()));

    vertices.append(VertexData(QVector3D(halfWidth, halfWidth, Length), QVector2D()));
    vertices.append(VertexData(QVector3D(-halfWidth, halfWidth, Length), QVector2D()));
    vertices.append(VertexData(QVector3D(-halfWidth, -halfWidth, Length), QVector2D()));
    vertices.append(VertexData(QVector3D(halfWidth, -halfWidth, Length), QVector2D()));


    for (unsigned int i = 0; i < 24; i += 8) {
        indices.append(0 + i);
        indices.append(1 + i);
        indices.append(2 + i);
        indices.append(0 + i);
        indices.append(2 + i);
        indices.append(3 + i);

        indices.append(4 + i);
        indices.append(7 + i);
        indices.append(6 + i);
        indices.append(4 + i);
        indices.append(6 + i);
        indices.append(5 + i);

        indices.append(0 + i);
        indices.append(4 + i);
        indices.append(5 + i);
        indices.append(0 + i);
        indices.append(5 + i);
        indices.append(1 + i);

        indices.append(3 + i);
        indices.append(2 + i);
        indices.append(6 + i);
        indices.append(3 + i);
        indices.append(6 + i);
        indices.append(7 + i);

        indices.append(0 + i);
        indices.append(7 + i);
        indices.append(4 + i);
        indices.append(0 + i);
        indices.append(3 + i);
        indices.append(7 + i);

        indices.append(1 + i);
        indices.append(5 + i);
        indices.append(6 + i);
        indices.append(1 + i);
        indices.append(6 + i);
        indices.append(2 + i);
    }

    m_arrayBuffer.allocate(vertices.constData(), vertices.size() * sizeof(vertices[0]));
    m_indexBuffer.allocate(indices.constData(), indices.size() * sizeof(indices[0]));
}
