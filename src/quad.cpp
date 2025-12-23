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
 * @brief Constructeur de la classe Quad.
 * 
 * @param origin_value Le point central du quadrilatère.
 * @param width_value Le vecteur représentant la largeur totale.
 * @param height_value Le vecteur représentant la hauteur totale.
 * @param mat Le matériau de la surface.
 */
Quad::Quad(Vector3f origin_value, Vector3f width_value, Vector3f height_value, const Material& mat) : 
    Shape(mat), origin(origin_value), width(width_value), height(height_value) {
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
 * @brief Teste l'intersection entre un rayon et le quadrilatère.
 * 
 * L'origine du Quad est considérée comme étant son CENTRE.
 * 
 * @param ray Le rayon à tester.
 * @param t_min Distance minimum valide.
 * @param t_max Distance maximum valide.
 * @param info Structure à remplir si intersection.
 * @return true si intersection trouvée dans l'intervalle [t_min, t_max].
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
    // L'équation du plan passe par 'origin' (qui est le centre ici)
    float t = (origin - ray.getOrigin()).dot(N) / denom;

    // Vérification si l'intersection est dans l'intervalle valide
    if (t < t_min || t > t_max) {
        return false;
    }

    // Calcul du point d'intersection exact dans l'espace
    Vector3f I = ray.getOrigin() + ray.getDirection() * t;
    
    // Vecteur allant du CENTRE (origin) vers le point d'intersection
    Vector3f V = I - origin;

    // Projection de V sur les axes définis par width et height
    float dot_w = V.dot(width);
    float dot_h = V.dot(height);
    float width_sq_len = width.dot(width);
    float height_sq_len = height.dot(height);
    
    // Coordonnées paramétriques (u, v) normalisées
    // u représente la position relative sur l'axe width
    // v représente la position relative sur l'axe height
    float u = dot_w / width_sq_len;
    float v = dot_h / height_sq_len;
    
    // LOGIQUE CENTRE :
    // Puisque l'origine est au centre, le quad s'étend de -0.5 à +0.5 
    // le long de ses axes de largeur et de hauteur.
    if (std::abs(u) <= 0.5f && std::abs(v) <= 0.5f) {
        // Remplissage de la structure HitInfo
        info.distance = t;
        info.point = I;
        // On s'assure que la normale pointe vers le rayon incident (recto/verso)
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