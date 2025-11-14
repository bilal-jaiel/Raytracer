#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include "vector3f.h"

class Sphere : public Shape {
private:
    float radius;
    Vector3f origin;

public:
    Sphere(float radius_value, Vector3f origin_value, const Material& mat);
    float getRadius() const;
    Vector3f getOrigin() const;
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif