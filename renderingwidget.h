#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

#include "cube.h"

class RenderingWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    RenderingWidget(QWidget *parent = 0);

    ~RenderingWidget();

protected:
    void resizeGL(int w, int h);
    void initializeGL();
    void paintGL();

    void initShaders();

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;

    Cube *cube;

    int m_step = 0;
};

#endif // RENDERINGWIDGET_H
