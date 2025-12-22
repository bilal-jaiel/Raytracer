/**
 * @file quad.h
 * @brief Classe représentant un quadrilatère dans la scène 3D
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef QUAD_H
#define QUAD_H

#include "shape.h"  
#include "vector3f.h"

/**
 * @class Quad
 * @brief Représente une surface plane quadrilatérale (ex: un rectangle ou un carré) dans l'espace 3D.
 *
 * Cette classe hérite de Shape et définit un plan borné par une origine et deux vecteurs
 * directeurs (largeur et hauteur).
 */
class Quad : public Shape {
private:
    /**
     * @brief Point d'origine du quadrilatère.
     */
    Vector3f origin;

    /**
     * @brief Vecteur définissant l'axe et la longueur de la largeur.
     */
    Vector3f width;

    /**
     * @brief Vecteur définissant l'axe et la longueur de la hauteur.
     */
    Vector3f height;


public:
    /**
     * @brief Constructeur de la classe Quad.
     *
     * Initialise un quadrilatère. Par défaut, il est placé à une distance de 5 unités
     * devant la caméra (Z = -5), avec une largeur et une hauteur de 2 unités.
     *
     * @param origin_value Position de l'origine du quad (Défaut: 0, 0, -5).
     * @param width_value Vecteur largeur (Défaut: 2, 0, 0).
     * @param height_value Vecteur hauteur (Défaut: 0, 2, 0).
     * @param mat Le matériau appliqué à la surface (Défaut: blanc translucide).
     */
    Quad(Vector3f origin_value = Vector3f(0.0f, 0.0f, -5.0f), 
         Vector3f width_value = Vector3f(2.0f, 0.0f, 0.0f), 
         Vector3f height_value = Vector3f(0.0f, 2.0f, 0.0f), 
         const Material& mat = Material());
    
    /**
     * @brief Accesseur pour l'origine.
     * @return Vector3f Le vecteur position de l'origine (ou du centre selon l'implémentation).
     */
    Vector3f getOrigin() const;

    /**
     * @brief Accesseur pour le vecteur largeur.
     * @return Vector3f Le vecteur définissant la largeur.
     */
    Vector3f getWidth() const;

    /**
     * @brief Accesseur pour le vecteur hauteur.
     * @return Vector3f Le vecteur définissant la hauteur.
     */
    Vector3f getHeight() const;

    /**
     * @brief Vérifie si un rayon intercepte le quadrilatère.
     *
     * Calcule le point d'intersection entre le rayon donné et le plan du quadrilatère,
     * puis vérifie si ce point se trouve à l'intérieur des bornes du quad.
     *
     * @param ray Le rayon lancé dans la scène.
     * @param t_min La distance minimale valide pour une intersection.
     * @param t_max La distance maximale valide pour une intersection.
     * @param info Structure de sortie contenant les détails de l'impact (point, normale, etc.) si collision il y a.
     * @return true Si le rayon touche le quadrilatère dans l'intervalle [t_min, t_max].
     * @return false Sinon.
     */
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif