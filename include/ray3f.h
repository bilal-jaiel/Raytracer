/**
 * @file ray3f.h
 * @brief Classe représentant un rayon de lumière
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef RAY3F_H
#define RAY3F_H

#include "vector3f.h"

/**
 * @class Ray3f
 * @brief Représente un rayon (demi-droite) dans l'espace 3D.
 *
 * Utilisé principalement pour le lancer de rayons (Ray Tracing).
 * Un rayon est défini par une équation paramétrique : P(t) = Origine + t * Direction.
 */
class Ray3f {
private:
    /**
     * @brief Point d'origine du rayon (point de départ).
     */
    Vector3f origin;

    /**
     * @brief Vecteur direction du rayon.
     */
    Vector3f direction;


public:
    /**
     * @brief Constructeur du rayon.
     *
     * Initialise un rayon avec une origine et une direction données.
     *
     * @param origin_value La position de départ du rayon (Défaut: 0,0,0).
     * @param direction_value La direction vers laquelle le rayon pointe (Défaut: 0,0,-1).
     */
    Ray3f(Vector3f origin_value = Vector3f(0.0f, 0.0f, 0.0f), Vector3f direction_value = Vector3f(0.0f, 0.0f, -1.0f));

    /**
     * @brief Accesseur pour l'origine.
     * @return Vector3f Le point d'origine du rayon.
     */
    Vector3f getOrigin() const;

    /**
     * @brief Accesseur pour la direction.
     * @return Vector3f Le vecteur direction du rayon.
     */
    Vector3f getDirection() const;
};

#endif