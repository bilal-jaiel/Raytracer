/**
 * @file scene.h
 * @brief Déclaration de la classe Scene, responsable de la gestion et du rendu d’une scène 3D
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include "camera.h"
#include "shape.h"
#include "ray3f.h"

/**
 * @class Scene
 * @brief Gère la scène 3D, les objets et le rendu
 */
class Scene {
private:
    Camera camera;
    std::vector<Shape*> shapes;
    Ray3f source;
    
    /**
     * @brief Initialise SDL et crée la fenêtre
     * @param width Largeur de la fenêtre
     * @param height Hauteur de la fenêtre
     * @param filename Titre de la fenêtre
     * @return true si l'initialisation réussit
     */
    bool initSDL(int width, int height, std::string filename);
    
    /**
     * @brief Trace un rayon et calcule sa couleur
     * @param ray Le rayon à tracer
     * @param depth Profondeur de récursion (pour les réflexions)
     * @return La couleur résultante
     */
    Vector3f traceRay(const Ray3f& ray, int depth);
    
    /**
     * @brief Calcule l'éclairage d'un point
     * @param hit Information sur l'intersection
     * @param lightPos Position de la lumière
     * @return Intensité de l'éclairage (0-1)
     */
    float calculateLighting(const HitInfo& hit, const Vector3f& lightPos);
    
    /**
     * @brief Vérifie si un point est dans l'ombre
     * @param point Point à tester
     * @param lightPos Position de la lumière
     * @return true si le point est dans l'ombre
     */
    bool isInShadow(const Vector3f& point, const Vector3f& lightPos);
    
    /**
     * @brief Génère un rayon pour un pixel donné
     * @param x Coordonnée x du pixel
     * @param y Coordonnée y du pixel
     * @param width Largeur de l'image
     * @param height Hauteur de l'image
     * @return Le rayon généré
     */
    Ray3f generateRay(int x, int y, int width, int height);
    
    /**
     * @brief Nettoie les ressources SDL
     */
    void cleanupSDL();

public:
    /**
     * @brief Constructeur de la scène
     * @param camera_value Caméra de la scène
     * @param shapes_values Vecteur d'objets de la scène
     * @param source_value Source de lumière
     */
    Scene(Camera camera_value, const std::vector<Shape*>& shapes_values, Ray3f source_value);
    
    /**
     * @brief Génère et affiche le rendu de la scène
     * @param width Largeur de l'image
     * @param height Hauteur de l'image
     * @param filename Nom du fichier/titre de la fenêtre
     */
    void render(int width, int height, std::string filename);
    
    /**
     * @brief Accesseur pour la caméra
     * @return La caméra de la scène
     */
    Camera getCamera() const;
    
    /**
     * @brief Accesseur pour les objets
     * @return Référence constante au vecteur d'objets
     */
    const std::vector<Shape*>& getShapes() const;
    
    /**
     * @brief Accesseur pour la source de lumière
     * @return La source de lumière
     */
    Ray3f getSource() const;
};

#endif