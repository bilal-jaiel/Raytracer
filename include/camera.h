/**
 * @file camera.h
 * @brief Classe représentant la caméra de la scène
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"
#include "ray3f.h"

/**
 * @class Camera
 * @brief Représente une caméra virtuelle dans un espace 3D.
 *
 * Cette classe gère la position et l'orientation de la caméra.
 * Elle pré-calcule un repère local orthonormé (Forward, Up, Right) lors de la construction
 * pour optimiser la génération des rayons.
 */
class Camera {
private:
    /**
     * @brief Position de l'œil de la caméra dans l'espace.
     */
    Vector3f position;

    /**
     * @brief Vecteur direction (Forward) normalisé.
     */
    Vector3f direction;

    /**
     * @brief Vecteur "Haut" (Up) du repère local de la caméra.
     * Recalculé pour être parfaitement perpendiculaire à la direction.
     */
    Vector3f up;

    /**
     * @brief Vecteur "Droite" (Right) du repère local de la caméra.
     * Calculé par produit vectoriel (Direction ^ Up_Monde).
     */
    Vector3f right;

public:
    /**
     * @brief Constructeur de la caméra.
     *
     * Initialise la position et l'orientation. Le constructeur calcule automatiquement
     * les vecteurs 'right' et 'up' finaux pour former un repère orthonormé.
     *
     * @param position_value Position initiale (Défaut: 0,0,0).
     * @param direction_value Direction du regard (Défaut: 0,0,-1).
     * @param up_value Vecteur indiquant le "haut" global (Défaut: 0,1,0).
     * @remark La convention choisie est le repère de la main droite (physique) :
     * - L'axe X positif pointe vers la droite de l'écran.
     * - L'axe Y positif pointe vers le haut de l'écran.
     * - L'axe Z positif pointe vers l'utilisateur (sort de l'écran).
     * Par conséquent, la caméra regarde par défaut vers les Z négatifs (vers l'intérieur de la scène).
     */
    Camera(Vector3f position_value = Vector3f(0.0f, 0.0f, 0.0f), 
           Vector3f direction_value = Vector3f(0.0f, 0.0f, -1.0f),
           Vector3f up_value = Vector3f(0.0f, 1.0f, 0.0f));

    /**
     *@brief Calcule le rayon pour un pixel donné.
     * Cette méthode transforme les coordonnées 2D de l'écran en un rayon 3D.
     * Elle projette un point sur le plan de vue situé devant la caméra en utilisant
     * le repère local (Forward, Right, Up).
     * @param u Coordonnée horizontale relative du pixel (de -1 à 1).
     * @param v Coordonnée verticale relative du pixel (de -1 à 1).
     * @param aspectRatio Ratio largeur/hauteur de l'image.
     * @return Ray3f Le rayon partant de l'œil vers ce pixel.
     */
    Ray3f getRay(float u, float v, float aspectRatio) const;

    // Accesseurs

    /**
     * @brief Accesseur pour la position.
     * @return Vector3f La position actuelle.
     */
    Vector3f getPosition() const;

    /**
     * @brief Accesseur pour la direction.
     * @return Vector3f Le vecteur direction normalisé.
     */
    Vector3f getDirection() const;
    
    /**
     * @brief Accesseur pour le vecteur Up local.
     * @return Vector3f Le vecteur haut recalculé.
     */
    Vector3f getUp() const;

    /**
     * @brief Accesseur pour le vecteur Right local.
     * @return Vector3f Le vecteur droite calculé.
     */
    Vector3f getRight() const;
};

#endif