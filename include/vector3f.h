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
};

#endif