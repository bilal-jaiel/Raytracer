/**
 * @file main.cpp
 * @brief Programme principal du projet PAP - Lancer de rayon
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include <iostream>
#include <vector>
#include "../include/vector3f.h"
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/sphere.h"
#include "../include/quad.h"
#include "../include/cube.h"
#include "../include/sdl_helper.h"

int main(int argc, char* argv[]) {
    // 1. Configuration de l'image
    const int width = 800;
    const int height = 600;
    const std::string filename = "rendu_final.ppm";

    std::cout << "Initialisation de la scene..." << std::endl;

    // 2. Création de la Caméra
    // Positionnée à l'extérieur de la boîte (z=8), regardant vers l'intérieur (z=-1)
    Camera cam(Vector3f(0.0f, 0.0f, 8.0f), Vector3f(0.0f, 0.0f, -1.0f));

    // 3. Création de la Source de Lumière (placée vers le haut de la boîte)
    // On définit une lumière ponctuelle via l'origine d'un Ray3f
    Ray3f lightSource(Vector3f(0.0f, 4.5f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));

    // 4. Initialisation de la Scène
    Scene scene(cam, lightSource);

    // 5. Création des Matériaux
    Material matWhite(0.8f, 0.8f, 0.8f, 0.0f);   // Murs mats
    Material matRed(0.9f, 0.1f, 0.1f, 0.0f);     // Mur rouge
    Material matGreen(0.1f, 0.9f, 0.1f, 0.0f);   // Mur vert
    Material matMirror(1.0f, 1.0f, 1.0f, 0.6f);  // Sphère semi-miroir
    Material matBlue(0.1f, 0.1f, 0.9f, 0.0f);    // Cube bleu

    // 6. Ajout des 5 Quads pour former la boîte (Taille 10x10x10)
    // Sol
    scene.addShape(new Quad(Vector3f(0, -5, 0), Vector3f(10, 0, 0), Vector3f(0, 0, 10), matWhite));
    // Plafond
    scene.addShape(new Quad(Vector3f(0, 5, 0), Vector3f(10, 0, 0), Vector3f(0, 0, 10), matWhite));
    // Mur du fond
    scene.addShape(new Quad(Vector3f(0, 0, -5), Vector3f(10, 0, 0), Vector3f(0, 10, 0), matWhite));
    // Mur gauche (Rouge)
    scene.addShape(new Quad(Vector3f(-5, 0, 0), Vector3f(0, 0, 10), Vector3f(0, 10, 0), matRed));
    // Mur droit (Vert)
    scene.addShape(new Quad(Vector3f(5, 0, 0), Vector3f(0, 0, 10), Vector3f(0, 10, 0), matGreen));

    // 7. Ajout de la Sphère et du Cube (objets internes)
    // Une sphère un peu brillante
    scene.addShape(new Sphere(2.0f, Vector3f(-2.0f, -3.0f, -2.0f), matMirror));

    // Un cube bleu tourné (en utilisant ton constructeur de Cube)
    // Note : On utilise des vecteurs unitaires pour l'orientation
    scene.addShape(new Cube(Vector3f(2.0f, -3.5f, 1.0f), 3.0f, matBlue, 
                            Vector3f(1.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f)));

    // 8. Calcul du rendu
    std::vector<Vector3f> imageBuffer;
    scene.render(width, height, filename, imageBuffer);

    // 9. Affichage SDL
    try {
        SdlHelper sdl(width, height, "Projet PAP - Lancer de Rayon");
        sdl.draw(imageBuffer);
        std::cout << "Affichage reussi. Fermez la fenetre pour quitter." << std::endl;
        sdl.waitForExit();
    } catch (const std::exception& e) {
        std::cerr << "Erreur SDL : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}