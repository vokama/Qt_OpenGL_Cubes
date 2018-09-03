#include "worldaxis.h"

#include <QVector>

WorldAxis::WorldAxis()
    : m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    initShaders();

    float width = 1.0f;
    float length = 10.0f;

    float halfWidth = width / 2.0f;

    // X Axis
    m_vertices.push_back(VertexData(QVector3D(0, halfWidth, halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(0, halfWidth, -halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(0, -halfWidth, -halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(0, -halfWidth, halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));

    m_vertices.push_back(VertexData(QVector3D(length, halfWidth, halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(length, halfWidth, -halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(length, -halfWidth, -halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(length, -halfWidth, halfWidth), QVector4D(1.0, 0.0, 0.0, 1.0)));

    // Y Axis
    m_vertices.push_back(VertexData(QVector3D(-halfWidth, 0, halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(-halfWidth, 0, -halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(halfWidth, 0, -halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(halfWidth, 0, halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));

    m_vertices.push_back(VertexData(QVector3D(-halfWidth, length, halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(-halfWidth, length, -halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(halfWidth, length, -halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(halfWidth, length, halfWidth), QVector4D(0.0, 1.0, 0.0, 1.0)));

    // Z Axis
    m_vertices.push_back(VertexData(QVector3D(halfWidth, halfWidth, length), QVector4D(0.0, 0.0, 1.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(-halfWidth, halfWidth, length), QVector4D(0.0, 0.0, 1.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(-halfWidth, -halfWidth, length), QVector4D(0.0, 0.0, 1.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(halfWidth, -halfWidth, length), QVector4D(0.0, 0.0, 1.0, 1.0)));

    m_vertices.push_back(VertexData(QVector3D(halfWidth, halfWidth, 0), QVector4D(0.0, 0.0, 1.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(-halfWidth, halfWidth, 0), QVector4D(0.0, 0.0, 1.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(-halfWidth, -halfWidth, 0), QVector4D(0.0, 0.0, 1.0, 1.0)));
    m_vertices.push_back(VertexData(QVector3D(halfWidth, -halfWidth, 0), QVector4D(0.0, 0.0, 1.0, 1.0)));


    for (unsigned int i = 0; i < 24; i += 8) {
        m_indices.push_back(0 + i);
        m_indices.push_back(1 + i);
        m_indices.push_back(2 + i);
        m_indices.push_back(0 + i);
        m_indices.push_back(2 + i);
        m_indices.push_back(3 + i);

        m_indices.push_back(4 + i);
        m_indices.push_back(7 + i);
        m_indices.push_back(6 + i);
        m_indices.push_back(4 + i);
        m_indices.push_back(6 + i);
        m_indices.push_back(5 + i);

        m_indices.push_back(0 + i);
        m_indices.push_back(4 + i);
        m_indices.push_back(5 + i);
        m_indices.push_back(0 + i);
        m_indices.push_back(5 + i);
        m_indices.push_back(1 + i);

        m_indices.push_back(3 + i);
        m_indices.push_back(2 + i);
        m_indices.push_back(6 + i);
        m_indices.push_back(3 + i);
        m_indices.push_back(6 + i);
        m_indices.push_back(7 + i);

        m_indices.push_back(0 + i);
        m_indices.push_back(7 + i);
        m_indices.push_back(4 + i);
        m_indices.push_back(0 + i);
        m_indices.push_back(3 + i);
        m_indices.push_back(7 + i);

        m_indices.push_back(1 + i);
        m_indices.push_back(5 + i);
        m_indices.push_back(6 + i);
        m_indices.push_back(1 + i);
        m_indices.push_back(6 + i);
        m_indices.push_back(2 + i);
    }

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_arrayBuffer.allocate(m_vertices.data(), m_vertices.size() * sizeof(m_vertices[0]));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer.allocate(m_indices.data(), m_indices.size() * sizeof(m_indices[0]));
    m_indexBuffer.release();
}

WorldAxis::~WorldAxis()
{
    m_arrayBuffer.destroy();
    m_indexBuffer.destroy();
}

void WorldAxis::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/waxis.vert"))
        exit(EXIT_FAILURE);

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.frag"))
        exit(EXIT_FAILURE);

    if (!m_program.link())
        exit(EXIT_FAILURE);
}

void WorldAxis::draw(const QMatrix4x4& viewProjectionMatrix)
{
    m_program.bind();

    m_program.setUniformValue("viewProjectionMatrix", viewProjectionMatrix);

    m_arrayBuffer.bind();

    int offset = 0;

    int vertLoc = 0;
    m_program.enableAttributeArray(vertLoc);
    m_program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(m_vertices[0]));
    offset += 3 * sizeof(float);

    int colourLoc = 6;
    m_program.enableAttributeArray(colourLoc);
    m_program.setAttributeBuffer(colourLoc, GL_FLOAT, offset, 4, sizeof(m_vertices[0]));
    offset += 4 * sizeof(float);

    m_arrayBuffer.release();

    m_indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_BYTE, 0);
    m_indexBuffer.release();

    m_program.disableAttributeArray(vertLoc);
    m_program.disableAttributeArray(colourLoc);

    m_program.release();
}
