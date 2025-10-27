#include "../include/sphere.h"

Sphere::Sphere(float radius_value, Vector3f origin_value) {
    radius = radius_value;
    origin = origin_value;
}

float Sphere::getRadius() const {
    return radius;
}

Vector3f Sphere::getOrigin() const {
    return origin;
}