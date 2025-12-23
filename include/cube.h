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
     * @brief Constructeur 2 : Basé sur la caméra + angles de rotation.
     * @param center_value Le centre.
     * @param size_value La taille.
     * @param mat Le matériau.
     * @param camera_dir La direction de la caméra (servira de base).
     * @param rotation_x_radians Rotation autour de l'axe X local (Haut/Bas).
     * @param rotation_y_radians Rotation autour de l'axe Y local (Gauche/Droite).
     */
    Cube(Vector3f center_value, float size_value, const Material& mat, 
         Vector3f camera_dir, double rotation_x_radians, double rotation_y_radians);
    
    virtual ~Cube();

    Vector3f getCenter() const;
    float getSize() const;
    Vector3f getForwardVector() const;
    Vector3f getSecondaryVector() const;
    
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif