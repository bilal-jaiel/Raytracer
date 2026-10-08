/**
 * @file sphere.cpp
 * @brief Implémentation de la classe Sphere
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/sphere.h"
#include "../include/vector3f.h"
#include <cmath>

/**
 * @brief Constructeur de la sphère.
 * @param radius_value Rayon.
 * @param origin_value Centre.
 * @param mat Matériau.
 */
Sphere::Sphere(float radius_value, Vector3f origin_value, const Material& mat) 
    : Shape(mat), radius(radius_value), origin(origin_value) {
}

/** @return Le rayon de la sphère. */
float Sphere::getRadius() const {
    return radius;
}

/** @return Le centre de la sphère. */
Vector3f Sphere::getOrigin() const {
    return origin;
}

/**
 * @brief Teste l'intersection rayon-sphère via une équation du second degré.
 * @param ray Le rayon incident.
 * @param t_min Distance minimale.
 * @param t_max Distance maximale.
 * @param info Structure de résultat.
 * @return true si intersection.
 */
bool Sphere::is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const {
    // Vecteur entre l'origine du rayon et le centre de la sphère
    Vector3f OC = ray.getOrigin() - this->origin;

    // Coefficients de l'équation : at² + bt + c = 0
    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2.0f * OC.dot(ray.getDirection());
    float c = OC.dot(OC) - radius * radius;

    // Calcul du discriminant
    float discriminant = b * b - 4 * a * c;

    // Pas de solution réelle = le rayon passe à côté
    if (discriminant < 0.0f) {
        return false;
    }

    float sqrt_disc = std::sqrt(discriminant);

    // On cherche la racine la plus proche (t1) dans l'intervalle valide
    float root = (-b - sqrt_disc) / (2.0f * a);
    if (root < t_min || root > t_max) {
        // Sinon on teste la racine plus éloignée (t2)
        root = (-b + sqrt_disc) / (2.0f * a);
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    // Enregistrement des données de l'impact
    info.distance = root;
    info.point = ray.getOrigin() + ray.getDirection() * info.distance;
    
    // La normale est le vecteur partant du centre vers le point d'impact
    info.normal = (info.point - this->origin) / radius;
    info.material = getMatter();

    return true;
}