#ifndef QUAD_H
#define QUAD_H

#include "shape.h"  
#include "vector3f.h"

class Quad : public Shape {
private:
    Vector3f origin;
    Vector3f width;
    Vector3f height;


public:
    Quad(Vector3f origin_value =  Vector3f(0.0f, 0.0f, -5.0f), Vector3f width_value = Vector3f(2.0f, 0.0f, 0.0f), Vector3f height_value = Vector3f(0.0f, 2.0f, 0.0f));
    Vector3f getOrigin() const;
    Vector3f getWidth() const;
    Vector3f getHeight() const;
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif