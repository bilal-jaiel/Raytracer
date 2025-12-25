/**
 * @file shape.cpp
 * @brief Implémentation de la classe de base Shape
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/shape.h"

/**
 * @brief Constructeur par défaut.
 * Initialise une forme avec un matériau par défaut (blanc).
 */
Shape::Shape(){
    Material();
}

/**
 * @brief Constructeur avec matériau.
 * @param matter_value Le matériau à assigner à la forme.
 */
Shape::Shape(Material matter_value){
    matter = matter_value;
}

/** @return Le matériau associé à la forme. */
Material Shape::getMatter() const {
    return matter;
}

/**
 * @brief Calcule le rayon réfléchi suite à un impact.
 * @param incident Rayon arrivant sur la surface.
 * @param normal Normale de la surface au point d'impact.
 * @param hitPoint Coordonnées 3D du point d'impact.
 * @return Ray3f Le rayon réfléchi.
 */
Ray3f Shape::reflect(const Ray3f& incident, const Vector3f& normal, const Vector3f& hitPoint) {
    // Calcul de la direction de réflexion parfaite : R = D - 2(D·N)N
    Vector3f D = incident.getDirection();
    Vector3f R = D - normal * (2.0f * D.dot(normal));
    
    // On décale légèrement l'origine du nouveau rayon pour éviter que 
    // l'algorithme ne détecte un impact sur la surface de départ.
    const float EPSILON = 1e-4f;
    Vector3f newOrigin = hitPoint + normal * EPSILON;
    
    return Ray3f(newOrigin, R.normalize());
}