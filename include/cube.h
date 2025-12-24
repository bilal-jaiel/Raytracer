/**
 * @file cube.h
 * @brief Classe représentant un Cube orienté
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef CUBE_H
#define CUBE_H

#include "shape.h"
#include "quad.h"
#include "vector3f.h"
#include <vector>

/**
 * @class Cube
 * @brief Représente un cube défini par son centre, sa taille et deux vecteurs d'orientation.
 */
class Cube : public Shape {
private:
    /* Le centre du cube */
    Vector3f center;
    /* La longueur d'un côté */
    float size;
    /* Le premier vecteur de direction (ex: vers l'avant) */
    Vector3f forward_vector;
    /* Le deuxième vecteur pour fixer l'orientation (ex: vecteur vertical ou autre) */
    Vector3f orientation_vector;
    
    /* Stockage des 6 faces générées */
    std::vector<Quad*> faces;

    /**
     * @brief Génère la géométrie (les faces) en utilisant les attributs stockés.
     * Applique la projection pour s'assurer que les vecteurs sont orthogonaux.
     */
    void buildGeometry();

    /**
     * @brief Fonction mathématique pour tourner un vecteur autour d'un axe.
     * @param vector_to_rotate Le vecteur qu'on veut faire tourner.
     * @param rotation_axis L'axe autour duquel on tourne.
     * @param angle_radians L'angle de rotation.
     * @return Vector3f Le résultat de la rotation.
     */
    Vector3f computeRotation(Vector3f vector_to_rotate, Vector3f rotation_axis, float angle_radians);

public:
    /**
     * @brief Constructeur 1 : Définition manuelle avec deux vecteurs.
     * @param center_value Le centre.
     * @param size_value La taille.
     * @param mat Le matériau.
     * @param forward_dir Le vecteur principal.
     * @param secondary_dir Le second vecteur (pour stabiliser l'orientation).
     */
    Cube(Vector3f center_value, float size_value, const Material& mat, 
         Vector3f forward_dir, Vector3f secondary_dir);

/**
     * @brief Constructeur 2 : Génère un cube orienté par rapport au regard de l'utilisateur.
     * * Ce constructeur est particulièrement utile pour placer un objet "face à la caméra". 
     * L'orientation initiale du cube est calquée sur le vecteur de vue (camera_dir), 
     * puis ajustée par deux rotations locales.
     * * @param center_value Position du centre du cube dans la scène.
     * @param size_value Longueur des arêtes du cube.
     * @param mat Propriétés optiques (couleur, réflexion, etc.).
     * @param camera_dir Vecteur direction de la caméra servant de référence pour l'alignement.
     * @param rotation_x_radians Inclinaison locale (Tangage/Pitch) : fait basculer le cube vers le haut ou le bas par rapport à la vue.
     * @param rotation_y_radians Pivot local (Lacet/Yaw) : fait tourner le cube vers la gauche ou la droite par rapport à la vue.
     */
    Cube(Vector3f center_value, float size_value, const Material& mat, 
         Vector3f camera_dir, double rotation_x_radians, double rotation_y_radians);
    
    /** @brief Destructeur : libère la mémoire utilisée par les faces du cube. */
    virtual ~Cube();

    /** @brief Retourne la position du centre du cube. */
    Vector3f getCenter() const;

    /** @brief Retourne la longueur d'un côté du cube. */
    float getSize() const;

    /** @brief Retourne le vecteur de direction principale (l'avant du cube). */
    Vector3f getForwardVector() const;

    /** @brief Retourne le deuxième vecteur d'orientation (le haut ou le côté). */
    Vector3f getSecondaryVector() const;
    
    /** * @brief Teste si un rayon lumineux touche le cube.
     * @return true si le rayon intersecte l'une des 6 faces du cube.
     */
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif