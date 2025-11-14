/**
 * @file main.cpp
 * @brief Programme principal du raytracer
 * @author Votre nom
 * @date 2025
 */

#include "../include/scene.h"
#include "../include/camera.h"
#include "../include/sphere.h"
#include "../include/cube.h"
#include "../include/quad.h"
#include "../include/material.h"
#include "../include/vector3f.h"
#include "../include/ray3f.h"
#include <vector>

/**
 * @brief Point d'entrée du programme
 * @return 0 si succès
 */
int main() {
    // Dimensions de l'image
    const int WIDTH = 800;
    const int HEIGHT = 600;
    
    // Création de la caméra
    Camera camera(
        Vector3f(0.0f, 0.0f, 5.0f),      // Position de la caméra
        Vector3f(0.0f, 0.0f, -1.0f)      // Direction (regarde vers -Z)
    );
    
    // Création de la source de lumière (en haut de la scène)
    Ray3f lightSource(
        Vector3f(0.0f, 4.0f, 0.0f),      // Position de la lumière
        Vector3f(0.0f, -1.0f, 0.0f)      // Direction (vers le bas)
    );
    
    // Création des objets de la scène
    std::vector<Shape*> objects;
    
    // === CRÉATION DE LA BOÎTE (5 quads) ===
    const float BOX_SIZE = 10.0f;
    const float HALF_BOX = BOX_SIZE / 2.0f;
    
    // Matériaux pour les murs
    Material wallMaterial(0.7f, 0.7f, 0.7f, 0.1f); // Gris, peu réfléchissant
    
    // Mur arrière (Z-)
    objects.push_back(new Quad(
        Vector3f(-HALF_BOX, -HALF_BOX, -HALF_BOX),  // Coin bas-gauche
        Vector3f(BOX_SIZE, 0.0f, 0.0f),             // Largeur (X)
        Vector3f(0.0f, BOX_SIZE, 0.0f),             // Hauteur (Y)
        Material(0.8f, 0.3f, 0.3f, 0.1f)            // Mur rouge
    ));
    
    // Mur gauche (X-)
    objects.push_back(new Quad(
        Vector3f(-HALF_BOX, -HALF_BOX, -HALF_BOX),
        Vector3f(0.0f, 0.0f, BOX_SIZE),
        Vector3f(0.0f, BOX_SIZE, 0.0f),
        Material(0.3f, 0.8f, 0.3f, 0.1f)            // Mur vert
    ));
    
    // Mur droit (X+)
    objects.push_back(new Quad(
        Vector3f(HALF_BOX, -HALF_BOX, HALF_BOX),
        Vector3f(0.0f, 0.0f, -BOX_SIZE),
        Vector3f(0.0f, BOX_SIZE, 0.0f),
        Material(0.3f, 0.3f, 0.8f, 0.1f)            // Mur bleu
    ));
    
    // Plafond (Y+)
    objects.push_back(new Quad(
        Vector3f(-HALF_BOX, HALF_BOX, -HALF_BOX),
        Vector3f(BOX_SIZE, 0.0f, 0.0f),
        Vector3f(0.0f, 0.0f, BOX_SIZE),
        Material(0.9f, 0.9f, 0.9f, 0.1f)            // Plafond blanc
    ));
    
    // Sol (Y-)
    objects.push_back(new Quad(
        Vector3f(-HALF_BOX, -HALF_BOX, -HALF_BOX),
        Vector3f(BOX_SIZE, 0.0f, 0.0f),
        Vector3f(0.0f, 0.0f, BOX_SIZE),
        Material(0.6f, 0.6f, 0.6f, 0.1f)            // Sol gris
    ));
    
    // === AJOUT D'UNE SPHÈRE ===
    objects.push_back(new Sphere(
        1.5f,                                        // Rayon
        Vector3f(-2.0f, -2.5f, -2.0f),              // Position
        Material(1.0f, 0.2f, 0.2f, 0.7f)            // Rouge brillant, très réfléchissant
    ));
    
    // === AJOUT D'UN CUBE ===
    objects.push_back(new Cube(
        Vector3f(2.0f, -3.0f, -1.0f),               // Centre
        2.0f,                                        // Taille
        Material(0.2f, 0.8f, 1.0f, 0.5f)            // Cyan, moyennement réfléchissant
    ));
    
    // Création de la scène
    Scene scene(camera, objects, lightSource);
    
    // Rendu de la scène
    scene.render(WIDTH, HEIGHT, "Raytracing - ENSIIE PAP");
    
    // Libération de la mémoire
    for (size_t i = 0; i < objects.size(); ++i) {
        delete objects[i];
    }
    objects.clear();
    
    return 0;
}