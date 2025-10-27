#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"

class Camera {
private:
    Vector3f position;
    Vector3f direction;


public:
    Camera(Vector3f position_value = Vector3f(0.0f, 0.0f, 0.0f), Vector3f direction_value = Vector3f(0.0f, 0.0f, -1.0f));
    Vector3f getPosition() const;
    Vector3f getDirection() const;
};

#endif
 