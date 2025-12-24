/**
 * @file cube.cpp
 * @brief Implémentation de la classe Cube
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/cube.h"
#include <cmath>

/**
 * @brief Constructeur manuel par définition de vecteurs.
 * * Ce constructeur permet de définir précisément la construction et l'orientation 
 * du cube en fournissant deux vecteurs directeurs.
 * * @param center_value Point central du cube dans la scène.
 * @param size_value Longueur des arêtes du cube.
 * @param mat Propriétés du matériau appliqué à toutes les faces.
 * @param forward_dir Vecteur définissant l'axe principal (l'avant) du cube.
 * @param secondary_dir Vecteur définissant l'axe secondaire (le haut ou le côté) pour stabiliser l'orientation.
 */
Cube::Cube(Vector3f center_value, float size_value, const Material& mat, Vector3f forward_dir, Vector3f secondary_dir)
    : Shape(mat),
      center(center_value),
      size(size_value),
      forward_vector(forward_dir.normalize()),
      orientation_vector(secondary_dir.normalize())
{
    buildGeometry();
}


/**
 * @brief Constructeur par orientation relative à la caméra.
 * * Ce constructeur aligne d'abord le cube sur la direction de vue, puis applique 
 * des rotations locales (sur le cube) pour ajuster son inclinaison.
 * * @param center_value Position du centre du cube.
 * @param size_value Taille des arêtes.
 * @param mat Matériau du cube.
 * @param camera_dir Direction de référence (généralement celle de la caméra).
 * @param rotation_x_radians Angle de rotation autour de l'axe horizontal local (Haut/Bas).
 * @param rotation_y_radians Angle de rotation autour de l'axe vertical local (Gauche/Droite).
 */
Cube::Cube(Vector3f center_value, float size_value, const Material& mat, Vector3f camera_dir, double rotation_x_radians, double rotation_y_radians)
    : Shape(mat),
      center(center_value),
      size(size_value)
{
    // repère de base suivant la caméra
    Vector3f base_forward = camera_dir.normalize();
    
    /* Sécurité pour le produit vectoriel : si le haut du cube
    est alligné avec le haut global on change temporairement le haut globbal
    */
    Vector3f world_up(0.0f, 1.0f, 0.0f);
    if (std::abs(base_forward.dot(world_up)) > 0.99f) {
        world_up = Vector3f(1.0f, 0.0f, 0.0f);
    }
    
    //construction de la base orthonormée complète (Right, Up, Forward) basée sur la direction fournie.
    Vector3f base_right = world_up.cross(base_forward).normalize();
    Vector3f base_up = base_forward.cross(base_right).normalize();

    //application des rotations
    
    // Rotation Y
    Vector3f rotated_forward = computeRotation(base_forward, base_up, (float)rotation_y_radians);
    Vector3f rotated_right = computeRotation(base_right, base_up, (float)rotation_y_radians);

    // Rotation X
    rotated_forward = computeRotation(rotated_forward, rotated_right, (float)rotation_x_radians);
    Vector3f rotated_up = computeRotation(base_up, rotated_right, (float)rotation_x_radians);

    //vecteurs finaux qui serviront de base à la création des faces.
    forward_vector = rotated_forward.normalize();
    orientation_vector = rotated_up.normalize(); 

    // génération des faces avec la fonction buildgeometry
    buildGeometry();
}

/**
 * @brief Destructeur de la classe Cube.
 * * Libère proprement la mémoire dynamique allouée pour chacune des 6 faces (Quads) 
 * du cube afin d'éviter les fuites mémoire. Elle vide ensuite le vecteur de pointeurs.
 */
Cube::~Cube() {
    for (size_t i = 0; i < faces.size(); ++i) {
        delete faces[i];
    }
    faces.clear();
}

/**
 * @brief Applique une rotation à un vecteur autour d'un axe quelconque.
 * * Cette méthode utilise la formule de rotation de Rodrigues pour calculer la nouvelle 
 * position d'un vecteur après rotation.
 * * @param vector_to_rotate Le vecteur d'origine (v).
 * @param rotation_axis L'axe de rotation (k), qui doit être unitaire.
 * @param angle_radians L'angle de rotation en radians (alpha).
 * @return Vector3f Le vecteur après rotation.
 */
Vector3f Cube::computeRotation(Vector3f vector_to_rotate, Vector3f rotation_axis, float angle_radians) {
    float cos_a = std::cos(angle_radians);
    float sin_a = std::sin(angle_radians);
    
    // Terme 1 : v * cos
    Vector3f part1 = vector_to_rotate * cos_a;
    
    // Terme 2 : (k x v) * sin
    Vector3f part2 = rotation_axis.cross(vector_to_rotate) * sin_a;
    
    // Terme 3 : k * (k . v) * (1 - cos)
    float dot_product = rotation_axis.dot(vector_to_rotate);
    Vector3f part3 = rotation_axis * (dot_product * (1.0f - cos_a));
    
    return part1 + part2 + part3;
}

/**
 * @brief Génère la géométrie interne du cube (les 6 faces).
 * * Cette méthode calcule d'abord un repère local orthonormé (X, Y, Z) à partir
 * des vecteurs d'orientation. Elle utilise ensuite ces axes pour positionner
 * et instancier 6 objets Quads représentant les faces du cube.
 */
void Cube::buildGeometry() {
    float half = size / 2.0f;
    
    // Axe Principal (Z local)
    Vector3f AxisZ = forward_vector; 

    // projection du second vecteur
    // Formule : Proj = V2 - (V2 . Z) * Z
    Vector3f AxisY = orientation_vector - AxisZ * orientation_vector.dot(AxisZ);

    // Si les vecteurs étaient parallèles
    if (AxisY.length() < 0.001f) {
        // Fallback 1 : Axe X
        Vector3f fallback = Vector3f(1.0f, 0.0f, 0.0f);
        AxisY = fallback - AxisZ * fallback.dot(AxisZ);

        if (AxisY.length() < 0.001f) {
            fallback = Vector3f(0.0f, 0.0f, 1.0f);
            AxisY = fallback - AxisZ * fallback.dot(AxisZ);
        }
    }
    AxisY = AxisY.normalize();

    // Calcul du troisième axe (X local) par produit vectoriel
    Vector3f AxisX = AxisY.cross(AxisZ).normalize();


    // créations des faces
    Vector3f wVec = AxisX * size;
    Vector3f hVec = AxisY * size;
    Vector3f dVec = AxisZ * size;

    // Avant
    faces.push_back(new Quad(center + AxisZ * half, wVec, hVec, getMatter()));
    // Arrière
    faces.push_back(new Quad(center - AxisZ * half, wVec * -1.0f, hVec, getMatter()));
    // Droite
    faces.push_back(new Quad(center + AxisX * half, dVec * -1.0f, hVec, getMatter()));
    // Gauche
    faces.push_back(new Quad(center - AxisX * half, dVec, hVec, getMatter()));
    // Haut
    faces.push_back(new Quad(center + AxisY * half, wVec, dVec * -1.0f, getMatter()));
    // Bas
    faces.push_back(new Quad(center - AxisY * half, wVec, dVec, getMatter()));
}

/**
 * @brief Accesseur pour le centre du cube.
 * @return Vector3f Les coordonnées (x, y, z) du point central du cube.
 */
Vector3f Cube::getCenter() const { 
    return center; 
}

/**
 * @brief Accesseur pour la taille du cube.
 * @return float La longueur d'une arête (côté) du cube.
 */
float Cube::getSize() const { 
    return size; 
}

/**
 * @brief Accesseur pour le vecteur de direction principale.
 * @return Vector3f Le vecteur Forward normalisé représentant l'orientation frontale du cube.
 */
Vector3f Cube::getForwardVector() const {
    return forward_vector; 
}

/**
 * @brief Accesseur pour le vecteur d'orientation secondaire.
 * @return Vector3f Le vecteur normalisé servant de base pour le haut ou le côté du cube.
 */
Vector3f Cube::getSecondaryVector() const {
    return orientation_vector;
}

/**
 * @brief Détermine si un rayon touche l'une des faces du cube.
 * * Cette méthode itère sur les 6 quads (faces) composant le cube. Elle ne conserve 
 * que l'intersection la plus proche de l'origine du rayon pour garantir un rendu correct.
 * * @param ray Le rayon incident lancé depuis la caméra ou une autre source.
 * @param t_min La distance minimale d'intersection (pour éviter le "Shadow Acne").
 * @param t_max La distance maximale de recherche.
 * @param info Structure à remplir avec les détails de l'impact (normale, distance, couleur).
 * @return true Si le rayon touche au moins une face du cube dans l'intervalle donné.
 */
bool Cube::is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const {
    bool hitAnything = false;
    float closest = t_max;
    HitInfo tempInfo;
    
    for (size_t i = 0; i < faces.size(); ++i) {
        if (faces[i]->is_hit(ray, t_min, closest, tempInfo)) {
            hitAnything = true;
            closest = tempInfo.distance;
            info = tempInfo;
        }
    }
    return hitAnything;
}