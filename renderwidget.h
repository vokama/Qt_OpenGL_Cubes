#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <QMouseEvent>
#include <QKeyEvent>

#include "camera.h"
#include "cube.h"

enum moveKeys {
    keyFwd =   1,
    keyBack =  1 << 1,
    keyLeft =  1 << 2,
    keyRight = 1 << 3
};

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = 0);

    ~RenderWidget();

protected:
    void resizeGL(int w, int h) override;
    void initializeGL() override;
    void paintGL() override;

    void initShaders();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void processInput();

public:
    Cube *m_cube;

private:
    Camera camera;

    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QOpenGLShaderProgram m_program;

    time_t renderTime;
    int framesCount = 0;

    bool m_cameraControl;

    QPoint m_mouseInitPos;
    QPoint m_mouseLastPos;
    QPoint m_mouseShift;
    QVector3D m_camTurn;

    int m_moveKeysPressed = 0;
    QVector3D m_camPos;
};

#endif // RENDERINGWIDGET_H
