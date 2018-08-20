#include "cube.h"

Cube::Cube(QVector3D center, QVector3D rotation, float dimension)
    : m_center(center),
      m_rotation(rotation),
      m_dimension(dimension),
      m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    initGraphics();
}

void Cube::reset(QVector3D center, QVector3D rotation)
{
    m_center = center;
    m_rotation = rotation;

    initGraphics();
}

void Cube::initGraphics()
{
/*    float halfD = m_dimension / 2.0f;
    float absNormCoord = 1 / sqrt(2);
    QVector<VertexData> vertices(8);
    // front plane
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() + halfD, m_center.z() - halfD), QVector2D(0, 1), QVector3D(-absNormCoord, +absNormCoord, -absNormCoord)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() + halfD, m_center.z() - halfD), QVector2D(1, 1), QVector3D(+absNormCoord, +absNormCoord, -absNormCoord)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() - halfD, m_center.z() - halfD), QVector2D(1, 0), QVector3D(+absNormCoord, -absNormCoord, -absNormCoord)));
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() - halfD, m_center.z() - halfD), QVector2D(0, 0), QVector3D(-absNormCoord, -absNormCoord, -absNormCoord)));
    // back plane
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() + halfD, m_center.z() + halfD), QVector2D(1, 1), QVector3D(-absNormCoord, +absNormCoord, +absNormCoord)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() + halfD, m_center.z() + halfD), QVector2D(0, 1), QVector3D(+absNormCoord, +absNormCoord, +absNormCoord)));
    vertices.append(VertexData(QVector3D(m_center.x() + halfD, m_center.y() - halfD, m_center.z() + halfD), QVector2D(0, 0), QVector3D(+absNormCoord, -absNormCoord, +absNormCoord)));
    vertices.append(VertexData(QVector3D(m_center.x() - halfD, m_center.y() - halfD, m_center.z() + halfD), QVector2D(1, 0), QVector3D(-absNormCoord, -absNormCoord, +absNormCoord)));

    QVector<GLubyte> indices(36);
    // front
    indices.append(0);
    indices.append(1);
    indices.append(2);
    indices.append(0);
    indices.append(3);
    indices.append(2);
    // left
    indices.append(4);
    indices.append(0);
    indices.append(3);
    indices.append(4);
    indices.append(7);
    indices.append(3);
    // right
    indices.append(1);
    indices.append(5);
    indices.append(6);
    indices.append(1);
    indices.append(2);
    indices.append(6);
    // top
    indices.append(4);
    indices.append(5);
    indices.append(1);
    indices.append(4);
    indices.append(0);
    indices.append(1);
    // bottom
    indices.append(3);
    indices.append(2);
    indices.append(6);
    indices.append(3);
    indices.append(7);
    indices.append(6);
    // back
    indices.append(5);
    indices.append(4);
    indices.append(7);
    indices.append(5);
    indices.append(6);
    indices.append(7);

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertices.constData(), vertices.size() * sizeof(vertices[0]));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indices.constData(), indices.size() * sizeof(indices[0]));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage("C:\\Users\\Egor\\Desktop\\ses.ico").mirrored());*/

    float width_div_2 = m_dimension / 2.0f;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;
    for (int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();
}
