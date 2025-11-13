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

// La nouvelle signature, prête à être utilisée par le moteur de rendu
bool Quad::is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const {
    // Le calcul de la normale au plan reste identique
    Vector3f N = width.cross(height).normalize();

    // Le calcul du dénominateur reste identique
    float denom = ray.getDirection().dot(N);
    if (std::abs(denom) < 1e-6f) {
        return false; // Rayon parallèle au plan, pas d'intersection
    }

    // Calcul de la distance t de l'intersection avec le plan
    float t = (origin - ray.getOrigin()).dot(N) / denom;

    // --- CORRECTION CLÉ 1 : Vérification de l'intervalle ---
    // On vérifie si l'intersection se trouve dans la plage de distance valide.
    // C'est ici qu'on utilise t_min et t_max.
    if (t < t_min || t > t_max) {
        return false; // Intersection trop proche ou trop loin, on l'ignore
    }

    // Le reste du code n'est exécuté que si la distance t est valide
    Vector3f I = ray.getOrigin() + ray.getDirection() * t;
    Vector3f V = I - origin;

    // On vérifie si le point est dans les limites du rectangle
    // Optimisation : on compare les carrés pour éviter les sqrt() lents
    float dot_w = V.dot(width);
    float dot_h = V.dot(height);
    float width_sq_len = width.dot(width);
    float height_sq_len = height.dot(height);

    if (std::abs(dot_w) * 2.0f <= width_sq_len && std::abs(dot_h) * 2.0f <= height_sq_len) {
        // --- CORRECTION CLÉ 2 : Remplissage de la structure HitInfo ---
        info.distance = t;
        info.point = I;
        info.normal = N;
        info.material = getMatter(); // Assurez-vous que Shape a 'matter' en 'protected'

        return true; // C'est un hit valide !
    }

    return false; // Le point est sur le plan mais en dehors du rectangle
}
