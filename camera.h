#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>

class Camera
{
public:
    Camera();

    QMatrix4x4 move(QVector3D move);
    QMatrix4x4 rotate(QVector3D angle);
};

#endif // CAMERA_H
