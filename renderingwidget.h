#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>

#include "cube.h"

enum CamDirection {
    camDirectFwd =   1,
    camDirectBack =  1 << 1,
    camDirectLeft =  1 << 2,
    camDirectRight = 1 << 3
};

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = 0);

    ~RenderWidget();

protected:
    void resizeGL(int w, int h);
    void initializeGL();
    void paintGL();

    void initShaders();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QMatrix4x4 camRotate(QPoint mouseShift);
    void camMove(int direction);

    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QOpenGLShaderProgram m_program;

    Cube *m_cube;

    bool m_cameraControl;
    QPoint m_mouseInitPos;
    QPoint m_mouseLastPos;
    int m_camDirection = 0;

    QVector3D m_eye = {0.0f, 0.0f, 0.0f};
    QVector3D m_center = {0.0f, 0.0f, -5.0f};
    QVector3D m_up = {0, 1, 0};
};

#endif // RENDERINGWIDGET_H
