/**
 * @file ray3f.cpp
 * @brief Implémentation de la classe Ray3f
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/ray3f.h"

/**
 * @brief Constructeur d'un rayon.
 * @param origin_value Point de départ du rayon.
 * @param direction_value Vecteur direction (généralement normalisé).
 */
Ray3f::Ray3f(Vector3f origin_value, Vector3f direction_value)
    : origin(origin_value), direction(direction_value) {
}

/** @return L'origine du rayon. */
Vector3f Ray3f::getOrigin() const {
    return origin;
}

/** @return La direction du rayon. */
Vector3f Ray3f::getDirection() const {
    return direction;
}