#include "../include/quad.h"
#include "../include/vector3f.h"
#include <cmath>

Quad::Quad(Vector3f origin_value, Vector3f width_value, Vector3f height_value) {
    origin = origin_value;
    width = width_value;
    height = height_value;
}

Vector3f Quad::getOrigin() const {
    return origin;
}

Vector3f Quad::getWidth() const {
    return width;
}

Vector3f Quad::getHeight() const {
    return height;
}

bool Quad::is_hit(Ray3f ray) const {
    //Calcul de la normale au plan via le produit vectoriel
    Vector3f N = width.cross(height).normalize();

    //Vérification du dénominateur
    float denom = ray.getDirection().dot(N);
    if (std::abs(denom) < 1e-6f) {
        return false; // Rayon parallèle au plan
    }

    //Calcul de la distance t de l’intersection
    Vector3f p0 = origin;
    float t = (p0 - ray.getOrigin()).dot(N) / denom;
    if (t <= 1e-6f) {
        return false; // Intersection derrière l’origine du rayon
    }

    //Calcul du point d’intersection I = O + tD
    Vector3f I = ray.getOrigin() + ray.getDirection() * t;

    //Vérifie si le point I est dans les bornes du rectangle
    Vector3f V = I - origin;

    float width_len = width.length();
    float height_len = height.length();

    float dist_w = V.dot(width.normalize());
    float dist_h = V.dot(height.normalize());

    if (std::abs(dist_w) <= width_len / 2 && std::abs(dist_h) <= height_len / 2) {
        return true; //Le rayon touche le rectangle
    }

    return false; //Le rayon passe à côté
}
