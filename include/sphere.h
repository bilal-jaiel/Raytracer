/**
 * @file sphere.h
 * @brief Classe représentant une sphère
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include "vector3f.h"

/**
 * @class Sphere
 * @brief Représente une sphère dans l'espace 3D.
 *
 * Cette classe hérite de Shape et définit une surface sphérique par un point central
 * et un rayon. Elle implémente l'algorithme d'intersection rayon-sphère.
 */
class Sphere : public Shape {
private:
    /**
     * @brief Rayon de la sphère.
     */
    float radius;

    /**
     * @brief Position du centre de la sphère.
     */
    Vector3f origin;

public:
    /**
     * @brief Constructeur de la sphère.
     *
     * Initialise une sphère avec un rayon, une position et un matériau donnés.
     *
     * @param radius_value Le rayon de la sphère.
     * @param origin_value Les coordonnées du centre de la sphère.
     * @param mat Le matériau à appliquer sur la sphère.
     */
    Sphere(float radius_value, Vector3f origin_value, const Material& mat);

    /**
     * @brief Accesseur pour le rayon.
     * @return float La valeur du rayon.
     */
    float getRadius() const;

    /**
     * @brief Accesseur pour l'origine.
     * @return Vector3f Le point central de la sphère.
     */
    Vector3f getOrigin() const;

    /**
     * @brief Vérifie si un rayon intercepte la sphère.
     *
     * Résout l'équation quadratique d'intersection entre la droite du rayon et
     * la surface de la sphère.
     *
     * @param ray Le rayon lancé dans la scène.
     * @param t_min La distance minimale valide pour une intersection.
     * @param t_max La distance maximale valide pour une intersection.
     * @param info Structure de sortie pour stocker les informations de collision (point, normale).
     * @return true Si le rayon touche la sphère dans l'intervalle [t_min, t_max].
     * @return false Sinon.
     */
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif