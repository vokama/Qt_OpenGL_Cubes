#include "cube.h"

Cube::Cube(QVector3D center, QVector3D rotation, float dimension)
    : m_center(center),
      m_rotation(rotation),
      m_dimension(dimension),
      m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_arrayBuffer.allocate(cubeVertices, sizeof(cubeVertices));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer.allocate(cubeIndices, sizeof(cubeIndices));
    m_indexBuffer.release();

    m_instanceBuf.create();
    m_instanceBuf.bind();
    m_instanceBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_instanceBuf.allocate(m_instanceBufSize);
    m_instanceBuf.release();
}

Cube::~Cube()
{
    m_arrayBuffer.destroy();
    m_indexBuffer.destroy();
    m_instanceBuf.destroy();
}

void Cube::draw(QOpenGLShaderProgram& program)
{
    m_arrayBuffer.bind();
    int vertLoc = 0;
    program.enableAttributeArray(vertLoc);
    program.setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(VertexData));
    m_arrayBuffer.release();

    m_instanceBuf.bind();

    int offset = 0;

    int centerLoc = 1;
    program.enableAttributeArray(centerLoc);
    program.setAttributeBuffer(centerLoc, GL_FLOAT, offset, 3, sizeof(CubeInstance));
    glVertexAttribDivisor(centerLoc, 1);
    offset += 3 * sizeof(float);

    int modelMatLoc = 2;
    for (int i = 0; i < 4; i++) {
        program.enableAttributeArray(modelMatLoc + i);
        program.setAttributeBuffer(modelMatLoc + i, GL_FLOAT, offset, 4, sizeof(CubeInstance));
        glVertexAttribDivisor(modelMatLoc + i, 1);

        offset += 4 * sizeof(float);
    }

    m_instanceBuf.release();

    m_indexBuffer.bind();
    glDrawElementsInstanced(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_BYTE, 0, m_instances.size());
    m_indexBuffer.release();
}

void Cube::addInstance(const CubeInstance& instance)
{
    m_instances.push_back(instance);

    m_instanceBuf.bind();

    if (m_instances.size() * sizeof(m_instances[0]) > m_instanceBufSize) {
        m_instanceBufSize *= 2;
        m_instanceBuf.allocate(m_instances.data(), m_instanceBufSize);
    } else {
        auto bufPtr = m_instanceBuf.mapRange(
                    (m_instances.size() - 1) * sizeof(m_instances[0]),
                    sizeof(m_instances[0]),
                    QOpenGLBuffer::RangeInvalidate | QOpenGLBuffer::RangeWrite);
        memcpy(bufPtr, &(m_instances.back()), sizeof(m_instances.back()));
        m_instanceBuf.unmap();
    }

    m_instanceBuf.release();
}

void Cube::removeInstance(int idx)
{

}
