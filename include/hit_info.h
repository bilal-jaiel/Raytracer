/**
 * @file hit_info.h
 * @brief Structure représentant les information d'une collision d'un rayon avec un point
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef HIT_INFO_H
#define HIT_INFO_H

#include "vector3f.h"
#include "material.h"

/**
 * @struct HitInfo
 * @brief Structure contenant les détails d'une intersection entre un rayon et un objet.
 *
 * Cette structure regroupe toutes les informations nécessaires (distance, position,
 * orientation de la surface, propriétés du matériau) pour calculer la couleur
 * finale d'un pixel (shading).
 */
struct HitInfo {
    /**
     * @brief La distance entre l'origine du rayon et le point d'impact.
     * Généralement notée 't' dans l'équation paramétrique du rayon.
     */
    float distance;

    /**
     * @brief Les coordonnées exactes du point de collision dans l'espace 3D.
     */
    Vector3f point;

    /**
     * @brief Le vecteur normal à la surface au point d'impact.
     * Utilisé pour les calculs d'éclairage et de réflexion.
     */
    Vector3f normal;

    /**
     * @brief Le matériau de l'objet percuté.
     * Définit la couleur et les propriétés optiques de la surface.
     */
    Material material;
};

#endif