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

// La nouvelle signature, prête à être utilisée par le moteur de rendu
bool Sphere::is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const {
    Vector3f OC = ray.getOrigin() - this->origin;

    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2.0f * OC.dot(ray.getDirection());
    float c = OC.dot(OC) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0f) {
        return false; // Aucune intersection réelle
    }

    float sqrt_disc = std::sqrt(discriminant);

    // --- CORRECTION CLÉ 1 : Vérification de l'intervalle pour les deux solutions ---
    // On cherche la plus petite solution 'root' qui est dans l'intervalle [t_min, t_max]
    
    // Teste la première solution (la plus proche, t1)
    float root = (-b - sqrt_disc) / (2.0f * a);
    if (root < t_min || root > t_max) {
        // La première solution n'est pas valide, on teste la seconde (t2)
        root = (-b + sqrt_disc) / (2.0f * a);
        if (root < t_min || root > t_max) {
            return false; // La seconde n'est pas valide non plus
        }
    }

    // Si on arrive ici, c'est que 'root' contient une distance d'intersection valide.

    // --- CORRECTION CLÉ 2 : Remplissage de la structure HitInfo ---
    info.distance = root;
    info.point = ray.getOrigin() + ray.getDirection() * info.distance;
    info.normal = (info.point - this->origin) / radius; // Pour une sphère, (P-C)/r donne la normale
    info.material = getMatter(); // On copie le matériau de la sphère

    return true; // C'est un hit valide !
}