/**
 * @file camera.cpp
 * @brief Implémentation optimisée de la classe Camera
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/camera.h"

/**
 * @brief Constructeur de la classe Camera.
 * * Ce constructeur initialise la position et normalise la direction de la caméra. Il génère
 * ensuite un repère local orthonormé (Right, Up, Forward) en utilisant le  produit vectoriel.
 * * @param position_value Position de la caméra dans l'espace 3D.
 * @param direction_value Direction vers laquelle la caméra pointe.
 * @param up_value Vecteur de référence pour le "haut" global (généralement 0,1,0).
 * * @remark Le calcul assure que 'right' et 'up' sont strictement perpendiculaires 
 * à la direction de vue, même si le 'up_value' fourni ne l'est pas.
 */
Camera::Camera(Vector3f position_value, Vector3f direction_value, Vector3f up_value) 
    : position(position_value),
      direction(direction_value.normalize()) // Normalisation pour garantir des calculs de rayons unitaires
{
    // Calcul du vecteur Right : produit vectoriel entre la direction et le haut global.
    // le résultat est perpendiculaire au plan formé par ces deux vecteurs.
    Vector3f tempRight = this->direction.cross(up_value);

    // Cas limite : si la direction est parallèle au vecteur Up global (regard vertical),
    // le produit vectoriel est nul. On définit alors un vecteur Right par défaut.
    if (tempRight.length() < 1e-5) {
        this->right = Vector3f(1.0f, 0.0f, 0.0f); // Défaut sur l'axe X
    } else {
        this->right = tempRight.normalize();
    }

    // Calcul du vecteur Up local (le "haut" (local) de la caméra).
    // On effectue le produit vectoriel entre Right et Direction.
    // Cela garantit que Up est à 90 degré de Direction ET de Right.
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
    // FOV par défau à 1
    float scale = 1.0f; 

    // on translate le point le long de l'axe 'right'.
    // On multiplie par aspectRatio pour compenser l'étirement dû à la largeur de l'écran.
    Vector3f horizontalOffset = this->right * (u * aspectRatio * scale);

    // De même mais verticalement
    Vector3f verticalOffset = this->up * (v * scale);

    // La direction du rayon est la somme de la direction de base avec les décalages calculés
    // On normalise le résultat pour obtenir un vecteur directionnel de longueur 1.
    Vector3f rayDir = (this->direction + horizontalOffset + verticalOffset).normalize();

    // la fonction renvoie alors le rayon partant de l'oeil jusqu'au pixel correspondant à (u,v,aspectRatio)
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