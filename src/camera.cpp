/**
 * @file camera.cpp
 * @brief Implémentation de la classe Camera
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/camera.h"

/**
 * @brief Constructeur de la classe Camera.
 *
 * Utilise une liste d'initialisation pour assigner directement la position et la direction.
 *
 * @param position_value La position initiale de la caméra.
 * @param direction_value La direction initiale de la caméra.
 */
Camera::Camera(Vector3f position_value, Vector3f direction_value) 
    : position(position_value), direction(direction_value) {
}

/**
 * @brief Récupère la position de la caméra.
 * @return Vector3f La position actuelle.
 */
Vector3f Camera::getPosition() const {
    return position;
}

/**
 * @brief Récupère la direction de la caméra.
 * @return Vector3f La direction actuelle.
 */
Vector3f Camera::getDirection() const {
    return direction;
}