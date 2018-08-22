#include "renderingwidget.h"

#include <QDesktopWidget>

#include <iostream>

RenderWidget::RenderWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_modelMatrix.setToIdentity();
    m_modelMatrix.translate(0.0f, 0.0f, -5.0f);
}

RenderWidget::~RenderWidget()
{}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5f, 0.4f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    m_cube = new Cube();
}

void RenderWidget::resizeGL(int w, int h)
{
    float aspect = w / (float)h;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45.0f, aspect, 0.1f, 10.0f);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camMove(m_camDirection);

    m_program.bind();
    m_program.setUniformValue("qt_ModelViewProjectionMatrix", m_projectionMatrix * m_viewMatrix * m_modelMatrix);
    m_program.setUniformValue("qt_Texture0", 0);

    m_cube->m_arrayBuffer.bind();

    int offset = 0;

    int vertLoc = m_program.attributeLocation("qt_Vertex");
    m_program.enableAttributeArray(vertLoc);
    m_program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texLoc = m_program.attributeLocation("qt_MultiTexCoord0");
    m_program.enableAttributeArray(texLoc);
    m_program.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    m_cube->m_indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, m_cube->m_indexBuffer.size(), GL_UNSIGNED_INT, 0);

    update();
}

void RenderWidget::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.vert"))
        close();

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.frag"))
        close();

    if (!m_program.link())
        close();
}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_cameraControl = true;

        grabMouse();
        grabKeyboard();
        this->setCursor(Qt::BlankCursor);

        m_mouseLastPos = m_mouseInitPos = event->globalPos();
    }
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_cameraControl)
        return;

    QPoint mouseCurrentPos = event->globalPos();

    //rotateCamera(mouseCurrentPos - m_mouseLastPos);

  //  m_viewMatrix = camRotate(mouseCurrentPos - m_mouseLastPos) * m_viewMatrix;
    m_mouseLastPos = mouseCurrentPos;
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_cameraControl = false;

        this->setCursor(Qt::ArrowCursor);
        releaseMouse();
        releaseKeyboard();

        QCursor c = cursor();
        c.setPos(m_mouseInitPos);
        this->setCursor(c);
    }
}

void RenderWidget::keyPressEvent(QKeyEvent *event)
{
    if (!m_cameraControl)
        return;

    int curKey = event->key();

    switch (curKey) {
    case Qt::Key_W:
        m_camDirection |= camDirectFwd;
        break;
    case Qt::Key_A:
        m_camDirection |= camDirectLeft;
        break;
    case Qt::Key_S:
        m_camDirection |= camDirectBack;
        break;
    case Qt::Key_D:
        m_camDirection |= camDirectRight;
        break;
    default:
        return;
    }
}

void RenderWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (!m_cameraControl)
        return;

    int curKey = event->key();

    switch (curKey) {
    case Qt::Key_W:
        m_camDirection &= ~camDirectFwd;
        break;
    case Qt::Key_A:
        m_camDirection &= ~camDirectLeft;
        break;
    case Qt::Key_S:
        m_camDirection &= ~camDirectBack;
        break;
    case Qt::Key_D:
        m_camDirection &= ~camDirectRight;
        break;
    default:
        break;
    }
}

QMatrix4x4 RenderWidget::camRotate(QPoint mouseShift)
{
    QVector3D shiftVec(mouseShift);
    shiftVec = -shiftVec;

    QMatrix4x4 rot;
    rot.rotate(shiftVec.x(), 0, 1, 0);
    rot.rotate(shiftVec.y(), 1, 0, 0);

//    m_eye = rot * m_eye;
//    m_up = rot * m_up;

    QMatrix4x4 cameraTransform;
    cameraTransform.lookAt(m_eye, m_center, m_up);
    return cameraTransform;
}

void RenderWidget::camMove(int direction)
{
    if (!direction)
        return;

    float step = 0.01f;
    QVector3D moveVec;
    if (direction & camDirectFwd)
        moveVec += QVector3D(0, 0, -step);
    if (direction & camDirectBack)
        moveVec += QVector3D(0, 0, step);
    if (direction & camDirectLeft)
        moveVec += QVector3D(-step, 0, 0);
    if (direction & camDirectRight)
        moveVec += QVector3D(step, 0, 0);

    QMatrix4x4 cameraTransform;
    cameraTransform.lookAt(m_eye + moveVec, m_center + moveVec, m_up);

    m_viewMatrix = cameraTransform * m_viewMatrix;
}

//void RenderWidget::rotateCamera(const QPoint mouseShift)
//{
//    QVector3D shiftVec(mouseShift);
//    shiftVec.setY(-shiftVec.y());  // координаты экрана отсчитываются с левого верхнего угла

//    QMatrix4x4 normalMat;
//    normalMat.rotate(90, 0.0, 0.0, 1.0);
//    QVector3D normal = normalMat * shiftVec;

//    std::cout << mouseShift.x() << ' ' << mouseShift.y() << '\n';
//    std::cout << normal.x() << ' ' << normal.y() << "\n\n";
//    m_viewMatrix.rotate(shiftVec.length(), normal);
//}
