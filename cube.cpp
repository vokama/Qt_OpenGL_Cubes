#include "cube.h"

Cube::Cube()
    : m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    initShaders();

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

void Cube::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/cube.vert"))
        exit(EXIT_FAILURE);

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.frag"))
        exit(EXIT_FAILURE);

    if (!m_program.link())
        exit(EXIT_FAILURE);
}

void Cube::draw(const QMatrix4x4& viewProjectionMatrix)
{
    m_program.bind();

    m_program.setUniformValue("viewProjectionMatrix", viewProjectionMatrix);

    m_arrayBuffer.bind();
    int vertLoc = 0;
    m_program.enableAttributeArray(vertLoc);
    m_program.setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(cubeVertices[0]));
    m_arrayBuffer.release();

    m_instanceBuf.bind();

    int offset = 0;

    int centerLoc = 1;
    m_program.enableAttributeArray(centerLoc);
    m_program.setAttributeBuffer(centerLoc, GL_FLOAT, offset, 3, sizeof(CubeInstance));
    glVertexAttribDivisor(centerLoc, 1);
    offset += 3 * sizeof(float);

    int modelMatLoc = 2;
    for (int i = 0; i < 4; i++) {
        m_program.enableAttributeArray(modelMatLoc + i);
        m_program.setAttributeBuffer(modelMatLoc + i, GL_FLOAT, offset, 4, sizeof(CubeInstance));
        glVertexAttribDivisor(modelMatLoc + i, 1);
        offset += 4 * sizeof(float);
    }

    m_instanceBuf.release();

    m_indexBuffer.bind();
    glDrawElementsInstanced(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(cubeIndices[0]), GL_UNSIGNED_BYTE, 0, m_instances.size());
    m_indexBuffer.release();

    m_program.disableAttributeArray(vertLoc);
    m_program.disableAttributeArray(centerLoc);
    for (int i = 0; i < 4; i++)
        m_program.disableAttributeArray(modelMatLoc + i);

    m_program.release();
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
