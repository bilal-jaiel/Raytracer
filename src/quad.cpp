/**
 * @file quad.cpp
 * @brief Implémentation de la classe Quad
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/quad.h"
#include "../include/vector3f.h"
#include <cmath>

/**
 * @brief Constructeur du quadrilatère.
 * @param origin_value Point central.
 * @param width_value Vecteur largeur.
 * @param height_value Vecteur hauteur.
 * @param mat Matériau.
 */
Quad::Quad(Vector3f origin_value, Vector3f width_value, Vector3f height_value, const Material& mat) : 
    Shape(mat), origin(origin_value), width(width_value), height(height_value) {
}

/** @return Le point central du quad. */
Vector3f Quad::getOrigin() const {
    return origin;
}

/** @return Le vecteur définissant la largeur. */
Vector3f Quad::getWidth() const {
    return width;
}

/** @return Le vecteur définissant la hauteur. */
Vector3f Quad::getHeight() const {
    return height;
}

/**
 * @brief Teste l'intersection rayon-quad.
 * @param ray Le rayon incident.
 * @param t_min Distance minimale.
 * @param t_max Distance maximale.
 * @param info Structure de résultat.
 * @return true si intersection.
 */
bool Quad::is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const {
    // Normale calculée par produit vectoriel des axes
    Vector3f N = width.cross(height).normalize();

    // Vérifie si le rayon n'est pas parallèle à la face
    float denom = ray.getDirection().dot(N);
    if (std::abs(denom) < 1e-6f) {
        return false;
    }

    // Distance d'intersection avec le plan infini
    float t = (origin - ray.getOrigin()).dot(N) / denom;

    // Vérifie si l'impact est dans l'intervalle de distance
    if (t < t_min || t > t_max) {
        return false;
    }

    // Calcul du point d'impact et de son décalage par rapport au centre
    Vector3f I = ray.getOrigin() + ray.getDirection() * t;
    Vector3f V = I - origin;

    // Coordonnées locales u et v par projection sur les axes
    float dot_w = V.dot(width);
    float dot_h = V.dot(height);
    float width_sq_len = width.dot(width);
    float height_sq_len = height.dot(height);
    
    float u = dot_w / width_sq_len;
    float v = dot_h / height_sq_len;
    
    // Le quad s'étend de -0.5 à 0.5 autour du centre
    if (std::abs(u) <= 0.5f && std::abs(v) <= 0.5f) {
        info.distance = t;
        info.point = I;
        
        // Oriente la normale face au rayon (gestion recto-verso)
        if (ray.getDirection().dot(N) > 0) {
            info.normal = N * -1.0f;
        } else {
            info.normal = N;
        }
        info.material = getMatter();
        
        return true;
    }

    return false;
}