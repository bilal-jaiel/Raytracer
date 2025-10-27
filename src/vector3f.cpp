#include "../include/vector3f.h"

Vector3f::Vector3f(float x_val, float y_val, float z_val) {
    x = x_val;
    y = y_val;
    z = z_val;
}

float Vector3f::getX() const {
    return x;
}

float Vector3f::getY() const {
    return y;
}

float Vector3f::getZ() const {
    return z;
}