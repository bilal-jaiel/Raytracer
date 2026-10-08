/**
 * @file vector3f.cpp
 * @brief Implémentation des opérations mathématiques sur les vecteurs 3D
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/vector3f.h"
#include <cmath>

/** @brief Addition de deux vecteur */
Vector3f Vector3f::operator+(const Vector3f& other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
}

/** @brief Soustraction de deux vecteurs */
Vector3f Vector3f::operator-(const Vector3f& other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
}

/** @brief Multiplication par un scalaire */
Vector3f Vector3f::operator*(float scalar) const {
    return Vector3f(x * scalar, y * scalar, z * scalar);
}

/** @brief Multiplication composante par composante (produit de Hadamard) */
Vector3f Vector3f::operator*(const Vector3f& other) const {
    return Vector3f(x * other.x, y * other.y, z * other.z);
}

/** @brief Division par un scalaire */
Vector3f Vector3f::operator/(float scalar) const {
    return Vector3f(x / scalar, y / scalar, z / scalar);
}

/** @brief Normalisation du vecteur (longueur unitaire) */
Vector3f Vector3f::normalize() const {
    float len = length();
    if (len < 1e-8f) return Vector3f(0, 0, 0);
    return (*this) * (1.0f / len);
}

/** @brief Calcul du produit vectoriel */
Vector3f Vector3f::cross(const Vector3f& other) const {
    return Vector3f(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

/** @brief Calcul de la norme (longueur) du vecteur */
float Vector3f::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

/** @brief Calcul du produit scalaire */
float Vector3f::dot(const Vector3f& other) const {
    return x * other.x + y * other.y + z * other.z;
}

/** @brief Constructeur par coordonnées */
Vector3f::Vector3f(float x_val, float y_val, float z_val) {
    x = x_val;
    y = y_val;
    z = z_val;
}

/** @return Composante X */
float Vector3f::getX() const { return x; }

/** @return Composante Y */
float Vector3f::getY() const { return y; }

/** @return Composante Z */
float Vector3f::getZ() const { return z; }