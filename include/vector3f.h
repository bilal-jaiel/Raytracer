#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f {
private:
    float x, y, z;


public:
    Vector3f(float x_val = 0.0f, float y_val = 0.0f, float z_val = 0.0f);

    float getX() const;
    float getY() const;
    float getZ() const;

    Vector3f operator+(const Vector3f& other) const;
    Vector3f operator-(const Vector3f& other) const;
    Vector3f operator*(float scalar) const;
    Vector3f operator/(float scalar) const;

    Vector3f normalize() const;
    Vector3f cross(const Vector3f& other) const;
    float length() const;
    float dot(const Vector3f& other) const;
};

#endif