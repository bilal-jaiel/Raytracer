/**
 * @file material.cpp
 * @brief Implémentation de la classe Material.
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/material.h"

/**
 * @brief Constructeur de la classe Material avec vérification des données.
 * * Initialise les propriétés du matériau et lève une exception si les valeurs 
 * fournies ne respectent pas les plages de validité (normalisation entre 0 et 1).
 * * @param r_value Intensité du rouge [0.0, 1.0].
 * @param g_value Intensité du vert [0.0, 1.0].
 * @param b_value Intensité du bleu [0.0, 1.0].
 * @param shininess_value Coefficient de réflexion ou brillance [0.0, 1.0].
 * * @throw std::invalid_argument Si une des valeurs RGB ou le shininess est hors de l'intervalle [0,1].
 */
Material::Material(float r_value, float g_value, float b_value, float shininess_value)
    : r(r_value), g(g_value), b(b_value), shininess(shininess_value) 
{
    // Vérification de la validité des couleurs
    if (r_value < 0 || r_value > 1 || g_value < 0 || g_value > 1 || b_value < 0 || b_value > 1) {
        throw std::invalid_argument("Les valeurs RGB doivent être normalisées (entre 0 et 1)");
    }
    
    // Vérification de la validité du coefficient de brillance
    if (shininess_value < 0 || shininess_value > 1) {
        throw std::invalid_argument("Le coefficient de réflexion (shininess) doit être compris entre 0 et 1");
    }
}

/**
 * @brief Retourne la composante rouge.
 * @return float Valeur entre 0.0 et 1.0.
 */
float Material::getR() const {
    return r;
}

/**
 * @brief Retourne la composante verte.
 * @return float Valeur entre 0.0 et 1.0.
 */
float Material::getG() const {
    return g;
}

/**
 * @brief Retourne la composante bleue.
 * @return float Valeur entre 0.0 et 1.0.
 */
float Material::getB() const {
    return b;
}

/**
 * @brief Retourne le coefficient de brillance/réflexion.
 * @return float Valeur entre 0.0 et 1.0.
 */
float Material::getShininess() const {
    return shininess;
}