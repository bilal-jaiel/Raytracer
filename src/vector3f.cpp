#include "../include/vector3f.h"
#include <cmath>

Vector3f Vector3f::operator+(const Vector3f& other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator-(const Vector3f& other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator*(float scalar) const {
    return Vector3f(x * scalar, y * scalar, z * scalar);
}

Vector3f Vector3f::operator*(const Vector3f& other) const {
    return Vector3f(
        this->x * other.x,
        this->y * other.y,
        this->z * other.z
    );
}

Vector3f Vector3f::operator/(float scalar) const {
    return Vector3f(x / scalar, y / scalar, z / scalar);
}

Vector3f Vector3f::normalize() const {
    float len = length();
    if (len < 1e-8f) return Vector3f(0,0,0);
    return (*this) * (1.0f / len);
}

Vector3f Vector3f::cross(const Vector3f& other) const {
    return Vector3f(
        y*other.z - z*other.y,
        z*other.x - x*other.z,
        x*other.y - y*other.x
    );
}

float Vector3f::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

float Vector3f::dot(const Vector3f& other) const {
    return x*other.x + y*other.y + z*other.z;
}

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