#include "cube.h"

Cube::Cube(QVector3D center, QVector3D rotation, float dimension)
    : m_center(center),
      m_rotation(rotation),
      m_dimension(dimension),
      m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    m_arrayBuffer.create();
    m_arrayBuffer.bind();

    m_indexBuffer.create();
    m_indexBuffer.bind();

    initGraphics();
}

Cube::~Cube()
{
    m_arrayBuffer.release();
    m_arrayBuffer.destroy();

    m_indexBuffer.release();
    m_indexBuffer.destroy();
}

void Cube::reset(QVector3D center, QVector3D rotation)
{
    m_center = center;
    m_rotation = rotation;

    initGraphics();
}

void Cube::initGraphics()
{
    float halfD = m_dimension / 2.0f;
    QVector<VertexData> vertices;
    // front plane
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() + halfD, m_center.z() + halfD), QVector2D(0, 1)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() + halfD, m_center.z() + halfD), QVector2D(1, 1)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() - halfD, m_center.z() + halfD), QVector2D(1, 0)));
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() - halfD, m_center.z() + halfD), QVector2D(0, 0)));
    // back plane
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() + halfD, m_center.z() - halfD), QVector2D(1, 1)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() + halfD, m_center.z() - halfD), QVector2D(0, 1)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() - halfD, m_center.z() - halfD), QVector2D(0, 0)));
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() - halfD, m_center.z() - halfD), QVector2D(1, 0)));

    QVector<GLuint> indices;
    // front
    indices.append(0);
    indices.append(2);
    indices.append(1);
    indices.append(0);
    indices.append(3);
    indices.append(2);
    // left
    indices.append(4);
    indices.append(3);
    indices.append(0);
    indices.append(4);
    indices.append(7);
    indices.append(3);
    // right
    indices.append(1);
    indices.append(6);
    indices.append(5);
    indices.append(1);
    indices.append(2);
    indices.append(6);
    // top
    indices.append(4);
    indices.append(1);
    indices.append(5);
    indices.append(4);
    indices.append(0);
    indices.append(1);
    // bottom
    indices.append(3);
    indices.append(6);
    indices.append(2);
    indices.append(3);
    indices.append(7);
    indices.append(6);
    // back
    indices.append(5);
    indices.append(7);
    indices.append(4);
    indices.append(5);
    indices.append(6);
    indices.append(7);

    m_arrayBuffer.allocate(vertices.constData(), vertices.size() * sizeof(vertices[0]));
    m_indexBuffer.allocate(indices.constData(), indices.size() * sizeof(indices[0]));
}
