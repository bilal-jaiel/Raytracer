/**
 * @file material.h
 * @brief Classe modélisant le matériau utilisé pour une forme
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef MATERIAL_H
#define MATERIAL_H

/**
 * @class Material
 * @brief Définit les propriétés optiques d'une surface.
 *
 * Cette classe encapsule les informations de couleur (RGB) et les propriétés
 * de réflexion ou de translucidité (shininess) nécessaires au rendu de l'objet.
 */
class Material {
private:
    /**
     * @brief Composantes de couleur Rouge (r), Verte (g) et Bleue (b).
     */
    float r, g, b;

    /**
     * @brief Coefficient de brillance ou de translucidité du matériau.
     */
    float shininess;


public:
    /**
     * @brief Constructeur du matériau.
     *
     * Initialise un matériau avec une couleur et un coefficient de brillance/translucidité donnés.
     * Par défaut, le matériau est blanc et à moitié translucide.
     *
     * @param r_value Composante Rouge (0.0 à 1.0). Défaut: 1.0.
     * @param g_value Composante Verte (0.0 à 1.0). Défaut: 1.0.
     * @param b_value Composante Bleue (0.0 à 1.0). Défaut: 1.0.
     * @param shininess_value Coefficient de brillance/translucidité. Défaut: 0.5.
     */
    Material(float r_value = 1.0f, float g_value = 1.0f, float b_value = 1.0f, float shininess_value = 0.5f);

    /**
     * @brief Accesseur pour la composante rouge.
     * @return float La valeur de la composante rouge de la couleur RGB.
     */
    float getR() const;

    /**
     * @brief Accesseur pour la composante verte.
     * @return float La valeur de la composante verte de la couleur RGB.
     */
    float getG() const;

    /**
     * @brief Accesseur pour la composante bleue.
     * @return float La valeur de la composante bleue de la couleur RGB.
     */
    float getB() const;

    /**
     * @brief Accesseur pour la propriété de brillance/translucidité.
     * @return float La valeur du coefficient de translucidité du matériau.
     */
    float getShininess() const;
};

#endif