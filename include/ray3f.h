#ifndef RAY3F_H
#define RAY3F_H

#include "vector3f.h"

class Ray3f {
private:
    Vector3f origin;
    Vector3f direction;


public:
    Ray3f(Vector3f origin_value = Vector3f(0.0f, 0.0f, 0.0f), Vector3f direction_value = Vector3f(0.0f, 0.0f, -1.0f));
    Vector3f getOrigin() const;
    Vector3f getDirection() const;
};

#endif