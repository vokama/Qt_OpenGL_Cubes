#include "camera.h"

#include <QVector3D>

Camera::Camera()
{}

QMatrix4x4 Camera::rotate(QVector3D turnVec)
{
    QMatrix4x4 cameraTransform;
    cameraTransform.rotate(turnVec.x(), 1, 0, 0);
    cameraTransform.rotate(turnVec.y(), 0, 1, 0);

    return cameraTransform;
}

QMatrix4x4 Camera::move(QVector3D move)
{
    QMatrix4x4 cameraTransform;
    cameraTransform.translate(move);

    return cameraTransform;
}
