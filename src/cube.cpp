/**
 * @file cube.cpp
 * @brief Implémentation de la classe Cube
 * @author Votre nom
 * @date 2025
 */

#include "../include/cube.h"

Cube::Cube(Vector3f center_value, float size_value, const Material& mat) : Shape(mat) {
    center = center_value;
    size = size_value;
    createFaces();
}

Cube::~Cube() {
    for (size_t i = 0; i < faces.size(); ++i) {
        delete faces[i];
    }
    faces.clear();
}

void Cube::createFaces() {
    float half = size / 2.0f;
    
    // CORRECTION: L'origine d'un Quad est le COIN INFÉRIEUR GAUCHE, pas le centre
    
    // Face avant (Z+) - coin inférieur gauche
    faces.push_back(new Quad(
        center + Vector3f(-half, -half, half),  // Coin bas-gauche
        Vector3f(size, 0.0f, 0.0f),             // Vers la droite
        Vector3f(0.0f, size, 0.0f),             // Vers le haut
        getMatter()
    ));
    
    // Face arrière (Z-) - coin inférieur droit (vu de l'extérieur)
    faces.push_back(new Quad(
        center + Vector3f(half, -half, -half),  // Coin bas-droite
        Vector3f(-size, 0.0f, 0.0f),            // Vers la gauche
        Vector3f(0.0f, size, 0.0f),             // Vers le haut
        getMatter()
    ));
    
    // Face droite (X+)
    faces.push_back(new Quad(
        center + Vector3f(half, -half, half),   // Coin bas-avant
        Vector3f(0.0f, 0.0f, -size),            // Vers l'arrière
        Vector3f(0.0f, size, 0.0f),             // Vers le haut
        getMatter()
    ));
    
    // Face gauche (X-)
    faces.push_back(new Quad(
        center + Vector3f(-half, -half, -half), // Coin bas-arrière
        Vector3f(0.0f, 0.0f, size),             // Vers l'avant
        Vector3f(0.0f, size, 0.0f),             // Vers le haut
        getMatter()
    ));
    
    // Face haut (Y+)
    faces.push_back(new Quad(
        center + Vector3f(-half, half, half),   // Coin avant-gauche
        Vector3f(size, 0.0f, 0.0f),             // Vers la droite
        Vector3f(0.0f, 0.0f, -size),            // Vers l'arrière
        getMatter()
    ));
    
    // Face bas (Y-)
    faces.push_back(new Quad(
        center + Vector3f(-half, -half, -half), // Coin arrière-gauche
        Vector3f(size, 0.0f, 0.0f),             // Vers la droite
        Vector3f(0.0f, 0.0f, size),             // Vers l'avant
        getMatter()
    ));
}

Vector3f Cube::getCenter() const {
    return center;
}

float Cube::getSize() const {
    return size;
}

bool Cube::is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const {
    bool hitAnything = false;
    float closest = t_max;
    HitInfo tempInfo;
    
    // Tester chaque face
    for (size_t i = 0; i < faces.size(); ++i) {
        if (faces[i]->is_hit(ray, t_min, closest, tempInfo)) {
            hitAnything = true;
            closest = tempInfo.distance;
            info = tempInfo;
        }
    }
    
    return hitAnything;
}