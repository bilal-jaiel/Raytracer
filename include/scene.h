/**
 * @file scene.h
 * @brief Déclaration de la classe Scene qui stocke les objets et calcule la couleur de chaque pixel (Raytracing).
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

class Scene {
private:
    Camera camera;
    
    // On garde les pointeurs bruts comme tu as choisi (plus simple)
    std::vector<Shape*> shapes;
    
    // La source de lumière
    Ray3f source;
    
    /**
     * @brief Trace un rayon dans la scène
     * @param ray Le rayon à lancer
     * @param depth Nombre de rebonds restants (pour la réflexion)
     * @return La couleur finale du pixel (RGB)
     */
    Vector3f traceRay(const Ray3f& ray, int depth);
    
    /**
     * @brief Calcule la couleur due à l'éclairage
     * @note Utilise 'this->source' pour la position de la lumière
     * @param hit L'info sur le point d'impact (position, normale...)
     * @return La couleur calculée
     */
    Vector3f calculateLighting(const HitInfo& hit);
    
    /**
     * @brief Teste si un point est caché de la lumière par un autre objet
     * @param point Le point à tester (décalé légèrement pour éviter l'acné)
     * @return true si le point est dans l'ombre
     */
    bool isInShadow(const Vector3f& point);

public:
    /**
     * @brief Constructeur
     * @param camera_value La caméra
     * @param source_value La lumière
     */
    Scene(Camera camera_value, Ray3f source_value);

    /**
     * @brief Destructeur. Libère la mémoire de tous les objets dans 'shapes'.
     */
    ~Scene();
    
    /**
     * @brief Ajoute un objet à la scène
     * @param shape Un pointeur vers l'objet (créé avec new)
     */
    void addShape(Shape* shape);
    
    /**
     * @brief Lance le calcul de l'image ET sauvegarde le résultat dans un fichier.
     * 
     * @param width Largeur de l'image (taille de la grille)
     * @param height Hauteur de l'image (taille de la grille)
     * @param filename Nom du fichier de sortie (ex: "image.ppm")
     * @param imageBuffer Référence vers le buffer pour qu'il soit aussi utilisable par SDL plus tard
     */
    void render(int width, int height, const std::string& filename, std::vector<Vector3f>& imageBuffer);
    
    // Accesseurs
    Camera getCamera() const;
    const std::vector<Shape*>& getShapes() const;
    Ray3f getSource() const;
};

#endif