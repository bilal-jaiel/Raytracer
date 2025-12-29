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

int main() {
    // Définition des dimensions de la fenêtre et du fichier de sortie
    const int width = 800;
    const int height = 600;
    const std::string filename = "rendu_final.ppm";

    std::cout << "Initialisation de la scene..." << std::endl;

    // Configuration de la caméra : placée en retrait sur l'axe Z pour englober la scène
    Camera cam(Vector3f(0.0f, 0.0f, 8.0f), Vector3f(0.0f, 0.0f, -1.0f));

    // Définition de la source lumineuse comme un point situé en haut de la boîte
    Ray3f lightSource(Vector3f(0.0f, 4.5f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));

    // Initialisation du moteur de rendu avec la caméra et la lumière
    Scene scene(cam, lightSource);

    // Préparation de la palette de matériaux (couleurs mates, miroirs et plastiques)
    Material matWhite(0.8f, 0.8f, 0.8f, 0.0f);   // Blanc neutre
    Material matRed(0.9f, 0.1f, 0.1f, 0.0f);     // Rouge vif
    Material matGreen(0.1f, 0.9f, 0.1f, 0.0f);   // Vert vif
    Material matMirror(1.0f, 1.0f, 1.0f, 0.6f);  // Surface réfléchissante
    Material matBlue(0.1f, 0.1f, 0.9f, 0.0f);    // Bleu profond

    // Construction de la "Cornell Box" en utilisant des Quads pour chaque mur
    // On crée ainsi un espace clos de 10x10x10 unités
    scene.addShape(new Quad(Vector3f(0, -5, 0), Vector3f(10, 0, 0), Vector3f(0, 0, 10), matWhite));  // Sol
    scene.addShape(new Quad(Vector3f(0, 5, 0), Vector3f(10, 0, 0), Vector3f(0, 0, 10), matWhite));   // Plafond
    scene.addShape(new Quad(Vector3f(0, 0, -5), Vector3f(10, 0, 0), Vector3f(0, 10, 0), matWhite));  // Fond
    scene.addShape(new Quad(Vector3f(-5, 0, 0), Vector3f(0, 0, 10), Vector3f(0, 10, 0), matRed));    // Gauche
    scene.addShape(new Quad(Vector3f(5, 0, 0), Vector3f(0, 0, 10), Vector3f(0, 10, 0), matGreen));   // Droite

    // Placement des objets d'intérêt à l'intérieur de la boîte
    // Une sphère avec un fort coefficient de réflexion pour tester les miroirs
    scene.addShape(new Sphere(2.0f, Vector3f(-2.0f, -3.0f, -2.0f), matMirror));

    // Un cube bleu avec une orientation personnalisée pour tester la géométrie complexe
    scene.addShape(new Cube(Vector3f(2.0f, -3.5f, 1.0f), 3.0f, matBlue, 
                            Vector3f(1.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f)));

    // Lancement du calcul de lancer de rayon et stockage des résultats dans le buffer
    std::vector<Vector3f> imageBuffer;
    scene.render(width, height, filename, imageBuffer);

    // Phase finale : affichage du rendu dans une fenêtre SDL
    try {
        SdlHelper sdl(width, height, "Projet PAP - Lancer de Rayon");
        sdl.draw(imageBuffer);
        
        std::cout << "Affichage reussi. Fermez la fenetre pour quitter." << std::endl;
        sdl.waitForExit();
        
    } catch (const std::exception& e) {
        // Gestion des erreurs liées à l'initialisation du système graphique
        std::cerr << "Erreur SDL : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}