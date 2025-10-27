#ifndef SHAPE_H
#define SHAPE_H

#include "material.h"
#include "ray3f.h"

class Shape {
private:
    Material matter;


public:
    virtual ~Shape() = default;
    Shape(Material matter);
    virtual bool is_hit(Ray3f ray) const = 0;
    virtual Ray3f reflect(Ray3f ray) const = 0;
    Material getMatter() const;
};

#endif