#include "../include/camera.h"

Camera::Camera(Vector3f position_value, Vector3f direction_value) {
    position = position_value;
    direction = direction_value;
}

Vector3f Camera::getPosition() const {
    return position;
}
Vector3f Camera::getDirection() const {
    return direction;
}