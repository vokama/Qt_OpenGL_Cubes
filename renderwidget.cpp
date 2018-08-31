#include "renderwidget.h"

#include "worldaxis.h"

#include <QDesktopWidget>
#include <QTimer>

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include <time.h>

RenderWidget::RenderWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_modelMatrix.setToIdentity();
    m_modelMatrix.translate(-5.0f, -5.0f, -5.0f);
}

RenderWidget::~RenderWidget()
{
    renderTime = time(NULL) - renderTime;
    std::cout << framesCount / renderTime << std::endl;
}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5f, 0.4f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    m_cube = new Cube(QVector3D(5, 5, 5));
    renderTime = time(NULL);
}

void RenderWidget::resizeGL(int w, int h)
{
    float aspect = w / (float)h;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45.0f, aspect, 0.1f, 1000.0f);
}

void RenderWidget::paintGL()
{
    processInput();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //WorldAxis worldAxis;

    //worldAxis.draw();

    m_viewMatrix.setToIdentity();
    m_viewMatrix = camera.move(m_camPos) * m_viewMatrix;
    m_viewMatrix = camera.rotate(m_camTurn) * m_viewMatrix;

    m_program.setUniformValue("qt_ViewProjectionMatrix", m_projectionMatrix * m_viewMatrix);

    m_cube->draw(m_program);

    framesCount++;

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

    if (!m_program.bind())
        close();
}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_cameraControl = true;

        grabMouse();
        grabKeyboard();
        //this->setCursor(Qt::BlankCursor);

        m_mouseLastPos = m_mouseInitPos = event->globalPos();
    }
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_cameraControl)
        return;

    QPoint mouseCurrentPos = event->globalPos();

    m_mouseShift = mouseCurrentPos - m_mouseLastPos;

    m_mouseLastPos = mouseCurrentPos;
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_cameraControl = false;

        this->setCursor(Qt::ArrowCursor);
        releaseMouse();
        releaseKeyboard();

        m_moveKeysPressed = 0;

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
        m_moveKeysPressed |= keyFwd;
        break;
    case Qt::Key_A:
        m_moveKeysPressed |= keyLeft;
        break;
    case Qt::Key_S:
        m_moveKeysPressed |= keyBack;
        break;
    case Qt::Key_D:
        m_moveKeysPressed |= keyRight;
        break;
    case Qt::Key_Right:
        m_mouseShift.setX(10);
        break;
    case Qt::Key_Left:
        m_mouseShift.setX(-10);
        break;
    case Qt::Key_Up:
        m_mouseShift.setY(-10);
        break;
    case Qt::Key_Down:
        m_mouseShift.setY(10);
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
        m_moveKeysPressed &= ~keyFwd;
        break;
    case Qt::Key_A:
        m_moveKeysPressed &= ~keyLeft;
        break;
    case Qt::Key_S:
        m_moveKeysPressed &= ~keyBack;
        break;
    case Qt::Key_D:
        m_moveKeysPressed &= ~keyRight;
        break;
    default:
        break;
    }
}

void RenderWidget::processInput()
{
    float turnSpeed = 0.1f;
    float moveSpeed = 0.1f;

    m_camTurn += QVector3D(m_mouseShift.y(), m_mouseShift.x(), 0) * turnSpeed;
    if (m_camTurn.x() > 90) {
        m_camTurn.setX(90);
    } else if (m_camTurn.x() < -90) {
        m_camTurn.setX(-90);
    }

    QVector3D move;
    if (m_moveKeysPressed & keyFwd)
        move.setZ(move.z() + 1);
    if(m_moveKeysPressed & keyBack)
        move.setZ(move.z() - 1);
    if(m_moveKeysPressed & keyRight)
        move.setX(move.x() - 1);
    if(m_moveKeysPressed & keyLeft)
        move.setX(move.x() + 1);
    move *= moveSpeed;

    /* применяем текущий поворот камеры */
    float xTurnRad = m_camTurn.x() * M_PI / 180.0f;
    float yTurnRad = m_camTurn.y() * M_PI / 180.0f;
    QVector3D rotatedMove;
    rotatedMove.setX(move.x() * cos(yTurnRad) + move.z() * -sin(yTurnRad) * cos(xTurnRad));
    rotatedMove.setY(move.z() * sin(xTurnRad));
    rotatedMove.setZ(move.z() * cos(yTurnRad) * cos(xTurnRad) + move.x() * sin(yTurnRad));

    m_camPos += rotatedMove;

    std::cout << m_camTurn.x() << ' ' << m_camTurn.y() << std::endl;
    std::cout << m_camPos.x() << ' ' << m_camPos.y() << ' ' << m_camPos.z() << std::endl << std::endl;
    m_mouseShift = QPoint();
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
