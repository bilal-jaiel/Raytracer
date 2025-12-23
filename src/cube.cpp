/**
 * @file cube.cpp
 * @brief Implémentation de la classe Cube
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/cube.h"
#include <cmath>

// --- CONSTRUCTEUR 1 : Manuel (2 vecteurs donnés explicitement) ---
Cube::Cube(Vector3f center_value, float size_value, const Material& mat, Vector3f forward_dir, Vector3f secondary_dir)
    : Shape(mat),
      center(center_value),
      size(size_value),
      forward_vector(forward_dir.normalize()),
      orientation_vector(secondary_dir.normalize())
{
    buildGeometry();
}

// --- CONSTRUCTEUR 2 : Basé sur la caméra + Rotations ---
Cube::Cube(Vector3f center_value, float size_value, const Material& mat, Vector3f camera_dir, double rotation_x_radians, double rotation_y_radians)
    : Shape(mat),
      center(center_value),
      size(size_value)
{
    // 1. On définit un repère de base aligné sur la caméra
    Vector3f base_forward = camera_dir.normalize();
    
    // On cherche un vecteur arbitraire pour construire le repère initial de la caméra
    Vector3f world_up(0.0f, 1.0f, 0.0f);
    if (std::abs(base_forward.dot(world_up)) > 0.99f) {
        world_up = Vector3f(1.0f, 0.0f, 0.0f);
    }
    
    Vector3f base_right = world_up.cross(base_forward).normalize();
    Vector3f base_up = base_forward.cross(base_right).normalize();

    // 2. On applique les rotations demandées (X et Y) sur ce repère
    
    // D'abord rotation Y (Yaw) autour de base_up
    Vector3f rotated_forward = computeRotation(base_forward, base_up, (float)rotation_y_radians);
    Vector3f rotated_right = computeRotation(base_right, base_up, (float)rotation_y_radians);

    // Ensuite rotation X (Pitch) autour du NOUVEAU vecteur right
    rotated_forward = computeRotation(rotated_forward, rotated_right, (float)rotation_x_radians);
    Vector3f rotated_up = computeRotation(base_up, rotated_right, (float)rotation_x_radians);

    // 3. On sauvegarde les vecteurs finaux dans les attributs de la classe
    forward_vector = rotated_forward.normalize();
    orientation_vector = rotated_up.normalize(); // On utilise le vecteur 'up' tourné comme second vecteur

    // 4. On construit
    buildGeometry();
}

Cube::~Cube() {
    for (size_t i = 0; i < faces.size(); ++i) {
        delete faces[i];
    }
    faces.clear();
}

/**
 * @brief Formule de Rodrigues pour la rotation vectorielle.
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

void Cube::buildGeometry() {
    float half = size / 2.0f;
    
    // Axe Principal (Z local)
    Vector3f AxisZ = forward_vector; 

    // --- PROJECTION DU SECOND VECTEUR ---
    // On rend 'secondaryVector' perpendiculaire à 'AxisZ'
    // Formule : Proj = V2 - (V2 . Z) * Z
    Vector3f AxisY = orientation_vector - AxisZ * orientation_vector.dot(AxisZ);

    // TEST DE SÉCURITÉ : Si les vecteurs étaient parallèles
    if (AxisY.length() < 0.001f) {
        // Fallback 1 : Axe X
        Vector3f fallback = Vector3f(1.0f, 0.0f, 0.0f);
        AxisY = fallback - AxisZ * fallback.dot(AxisZ);

        // Fallback 2 : Axe Z (si AxisZ était X)
        if (AxisY.length() < 0.001f) {
            fallback = Vector3f(0.0f, 0.0f, 1.0f);
            AxisY = fallback - AxisZ * fallback.dot(AxisZ);
        }
    }

    // Normalisation de l'axe secondaire (Y local)
    AxisY = AxisY.normalize();

    // Calcul du troisième axe (X local) par produit vectoriel
    Vector3f AxisX = AxisY.cross(AxisZ).normalize();


    // --- CRÉATION DES FACES ---
    Vector3f wVec = AxisX * size; // Largeur selon l'axe X local
    Vector3f hVec = AxisY * size; // Hauteur selon l'axe Y local
    Vector3f dVec = AxisZ * size; // Profondeur selon l'axe Z local

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

Vector3f Cube::getCenter() const { return center; }
float Cube::getSize() const { return size; }
Vector3f Cube::getForwardVector() const { return forward_vector; }
Vector3f Cube::getSecondaryVector() const { return orientation_vector; }

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