#include "../include/sphere.h"
#include "../include/vector3f.h"
#include <cmath>

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

bool Sphere::is_hit(Ray3f ray) const {
    // OC = O - C
    Vector3f OC = ray.getOrigin() - getOrigin();

    float a = ray.getDirection().dot(ray.getDirection()); // normalement = 1 si D est normalisé
    float b = 2.0f * OC.dot(ray.getDirection());
    float c = OC.dot(OC) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0f) {
        return false; // pas d'intersection
    }

    float sqrt_disc = std::sqrt(discriminant);
    float t1 = (-b - sqrt_disc) / (2.0f * a);
    float t2 = (-b + sqrt_disc) / (2.0f * a);

    const float EPSILON = 1e-4f;
    float t = 0.0f;

    if (t1 > EPSILON) {
        t = t1;
    } else if (t2 > EPSILON) {
        t = t2;
    } else {
        return false;
    }

    // Calcul du point d'intersection
    Vector3f I = ray.getOrigin() + ray.getDirection() * t;

    // Calcul du vecteur normal à la surface
    Vector3f N = (I - getOrigin()).normalize();

    return true;
}
