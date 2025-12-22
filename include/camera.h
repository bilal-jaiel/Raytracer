/**
 * @file camera.h
 * @brief Classe représentant la caméra de la scène
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"

/**
 * @class Camera
 * @brief Représente une caméra virtuelle dans un espace 3D.
 *
 * Cette classe gère la position et l'orientation (direction) de la caméra
 * pour le rendu de la scène.
 */
class Camera {
private:
    /**
     * @brief Position de la caméra dans l'espace.
     */
    Vector3f position;

    /**
     * @brief Direction vers laquelle la caméra regarde.
     */
    Vector3f direction;


public:
    /**
     * @brief Constructeur de la caméra.
     *
     * Initialise la caméra. Par défaut, on la place à l'origine du repère
     * et on la fait pointer vers l'avant selon la règle de la main droite (Z négatif).
     *
     * @param position_value La position initiale de la caméra (Défaut: 0,0,0).
     * @param direction_value Le vecteur direction de la vue (Défaut: 0,0,-1).
     */
    Camera(Vector3f position_value = Vector3f(0.0f, 0.0f, 0.0f), Vector3f direction_value = Vector3f(0.0f, 0.0f, -1.0f));

    /**
     * @brief Accesseur pour la position.
     * @return Vector3f La position actuelle de la caméra.
     */
    Vector3f getPosition() const;

    /**
     * @brief Accesseur pour la direction.
     * @return Vector3f Le vecteur direction actuel de la caméra.
     */
    Vector3f getDirection() const;
};

#endif