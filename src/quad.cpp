/**
 * @file quad.cpp
 * @brief Implémentation de la classe Quad
 */

#include "../include/quad.h"
#include "../include/vector3f.h"
#include <cmath>

Quad::Quad(Vector3f origin_value, Vector3f width_value, Vector3f height_value, const Material& mat) : Shape(mat) {
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

/**
 * @brief Teste l'intersection entre un rayon et le quadrilatère
 * @param ray Le rayon à tester
 * @param t_min Distance minimum
 * @param t_max Distance maximum
 * @param info Structure à remplir si intersection
 * @return true si intersection trouvée dans l'intervalle [t_min, t_max]
 */
bool Quad::is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const {
    // Calcul de la normale au plan (produit vectoriel width × height)
    Vector3f N = width.cross(height).normalize();

    // Calcul du dénominateur (direction du rayon · normale)
    float denom = ray.getDirection().dot(N);
    
    // Si le dénominateur est proche de 0, le rayon est parallèle au plan
    if (std::abs(denom) < 1e-6f) {
        return false;
    }

    // Calcul de la distance t de l'intersection avec le plan
    float t = (origin - ray.getOrigin()).dot(N) / denom;

    // Vérification si l'intersection est dans l'intervalle valide
    if (t < t_min || t > t_max) {
        return false;
    }

    // Calcul du point d'intersection
    Vector3f I = ray.getOrigin() + ray.getDirection() * t;
    
    // Vecteur du coin origin vers le point d'intersection
    Vector3f V = I - origin;

    // CORRECTION: Projection de V sur les axes width et height
    // On calcule les coordonnées paramétriques (u, v)
    float dot_w = V.dot(width);
    float dot_h = V.dot(height);
    float width_sq_len = width.dot(width);
    float height_sq_len = height.dot(height);
    
    // Coordonnées normalisées dans le plan du quad
    float u = dot_w / width_sq_len;
    float v = dot_h / height_sq_len;
    
    // Le point est dans le rectangle si 0 <= u <= 1 et 0 <= v <= 1
    if (u >= 0.0f && u <= 1.0f && v >= 0.0f && v <= 1.0f) {
        // Remplissage de la structure HitInfo
        info.distance = t;
        info.point = I;
        info.normal = N;
        info.material = getMatter();
        
        return true;
    }

    return false;
}