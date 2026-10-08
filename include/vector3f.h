/**
 * @file vector3f.h
 * @brief Classe définissant un vecteur 3D
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef VECTOR3F_H
#define VECTOR3F_H

/**
 * @class Vector3f
 * @brief Classe utilitaire mathématique représentant un vecteur ou un point dans un espace 3D.
 *
 * Fournit les opérations vectorielles de base (addition, soustraction, produits scalaire
 * et vectoriel, normalisation) nécessaires aux calculs géométriques et physiques.
 */
class Vector3f {
private:
    /**
     * @brief Les coordonnées du vecteur (x, y, z).
     */
    float x, y, z;


public:
    /**
     * @brief Constructeur du vecteur.
     *
     * @param x_val Coordonnée X (Défaut: 0.0).
     * @param y_val Coordonnée Y (Défaut: 0.0).
     * @param z_val Coordonnée Z (Défaut: 0.0).
     */
    Vector3f(float x_val = 0.0f, float y_val = 0.0f, float z_val = 0.0f);

    /**
     * @brief Accesseur pour la coordonnée X.
     * @return float La valeur de x.
     */
    float getX() const;

    /**
     * @brief Accesseur pour la coordonnée Y.
     * @return float La valeur de y.
     */
    float getY() const;

    /**
     * @brief Accesseur pour la coordonnée Z.
     * @return float La valeur de z.
     */
    float getZ() const;

    /**
     * @brief Addition vectorielle.
     * @param other Le vecteur à ajouter.
     * @return Vector3f Le résultat de (this + other).
     */
    Vector3f operator+(const Vector3f& other) const;

    /**
     * @brief Soustraction vectorielle.
     * @param other Le vecteur à soustraire.
     * @return Vector3f Le résultat de (this - other).
     */
    Vector3f operator-(const Vector3f& other) const;

    /**
     * @brief Multiplication par un scalaire.
     * @param scalar Le nombre par lequel multiplier le vecteur.
     * @return Vector3f Le vecteur mis à l'échelle.
     */
    Vector3f operator*(float scalar) const;

    /**
     * @brief Multiplication d'Hadamard par un vecteur.
     * @param other Le vacteur par lequel multiplier le vecteur d'origine.
     * @return Vector3f Le vecteur mis à l'échelle.
     */
    Vector3f operator*(const Vector3f& other) const;

    /**
     * @brief Division par un scalaire.
     * @param scalar Le nombre par lequel diviser le vecteur.
     * @return Vector3f Le vecteur réduit.
     */
    Vector3f operator/(float scalar) const;

    /**
     * @brief Normalise le vecteur.
     *
     * Retourne un vecteur unitaire (de longueur 1) pointant dans la même direction.
     *
     * @return Vector3f Le vecteur unitaire résultant.
     */
    Vector3f normalize() const;

    /**
     * @brief Produit vectoriel (Cross Product).
     *
     * Calcule un vecteur perpendiculaire aux deux vecteurs d'entrée.
     *
     * @param other L'autre vecteur.
     * @return Vector3f Le vecteur résultant du produit vectoriel.
     */
    Vector3f cross(const Vector3f& other) const;

    /**
     * @brief Calcule la norme (longueur) du vecteur.
     * @return float La longueur euclidienne du vecteur.
     */
    float length() const;

    /**
     * @brief Produit scalaire (Dot Product).
     *
     * Utilisé pour calculer l'angle entre deux vecteurs ou des projections.
     *
     * @param other L'autre vecteur.
     * @return float Le résultat scalaire du produit.
     */
    float dot(const Vector3f& other) const;
};

#endif