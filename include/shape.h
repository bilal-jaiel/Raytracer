#ifndef SHAPE_H
#define SHAPE_H

#include "material.h"
#include "ray3f.h"
#include "hit_info.h"

class Shape {
private:
    Material matter;


public:
    virtual ~Shape() = default;
    Shape();
    Shape(Material matter_value);
    virtual bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const = 0;
    Ray3f reflect(const Ray3f& incident, const Vector3f& normal, const Vector3f& hitPoint);
    
    Material getMatter() const;
};

#endif