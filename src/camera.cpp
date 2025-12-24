/**
 * @file camera.cpp
 * @brief Implémentation optimisée de la classe Camera
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/camera.h"

/**
 * @brief Constructeur de la classe Camera.
 *
 * Calcule immédiatement le repère local (Right, Up) à partir de la direction
 * et d'un vecteur vertical suggéré. Cela garantit un repère orthonormé
 * et évite de refaire ces calculs pour chaque pixel.
 *
 * @param position_value Position de la caméra.
 * @param direction_value Direction du regard.
 * @param up_value Vecteur indiquant le "haut" global (pour l'orientation).
 */
Camera::Camera(Vector3f position_value, Vector3f direction_value, Vector3f up_value) 
    : position(position_value),               // Initialisation directe
      direction(direction_value.normalize())  // Initialisation directe (avec calcul simple)
{
    // Le reste est trop complexe pour la liste, on le garde dans le corps
    
    // Calcul de Right (dépend de direction, déjà init)
    Vector3f tempRight = this->direction.cross(up_value);

    if (tempRight.length() < 1e-5) {
        this->right = Vector3f(1.0f, 0.0f, 0.0f);
    } else {
        this->right = tempRight.normalize();
    }

    // Calcul de Up (dépend de right, qui vient d'être calculé)
    this->up = this->right.cross(this->direction).normalize();
}

/**
 * @brief Génère un rayon pour un pixel (optimisé).
 * 
 * Utilise les vecteurs pré-calculés 'right' et 'up'.
 * 
 * @param u Coordonnée horizontale (-1 à 1).
 * @param v Coordonnée verticale (-1 à 1).
 * @param aspectRatio Ratio de l'écran.
 * @return Ray3f Le rayon calculé.
 */
Ray3f Camera::getRay(float u, float v, float aspectRatio) const {
    
    float scale = 1.0f; // Facteur de zoom (FOV standard)

    // Déplacement sur le plan de l'écran virtuel en utilisant le repère local
    Vector3f horizontalOffset = this->right * (u * aspectRatio * scale);
    Vector3f verticalOffset = this->up * (v * scale);

    // Direction finale = (Forward + DécalageDroit + DécalageHaut) normalisée
    Vector3f rayDir = (this->direction + horizontalOffset + verticalOffset).normalize();

    return Ray3f(this->position, rayDir);
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

/**
 * @brief Récupère le vecteur Up local calculé.
 * @return Vector3f Le vecteur haut.
 */
Vector3f Camera::getUp() const {
    return up;
}

/**
 * @brief Récupère le vecteur Right local calculé.
 * @return Vector3f Le vecteur droite.
 */
Vector3f Camera::getRight() const {
    return right;
}