#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f {
private:
    float x, y, z;


public:
    Vector3f(float x_val, float y_val, float z_val);
    float getX() const;
    float getY() const;
    float getZ() const;
};

#endif