/**
 * @file scene.cpp
 * @brief Implémentation de la classe Scene (Cœur du Raytracer)
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/scene.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include <algorithm>

// Constante pour éviter l'auto-intersection (Shadow Acne)
const float EPSILON = 1e-4f;
const float INFINITY_FLT = std::numeric_limits<float>::max();

/**
 * @brief Constructeur de la scène.
 * @param camera_value Caméra de la scène.
 * @param source_value Position et direction de la lumière.
 */
Scene::Scene(Camera camera_value, Ray3f source_value)
    : camera(camera_value), source(source_value) {
}

/**
 * @brief Destructeur : Nettoie la mémoire des objets (Shapes) alloués avec 'new'.
 */
Scene::~Scene() {
    for (Shape* s : shapes) {
        delete s;
    }
    shapes.clear();
}

/**
 * @brief Ajoute une forme géométrique à la scène.
 * @param shape Pointeur vers l'objet à ajouter.
 */
void Scene::addShape(Shape* shape) {
    shapes.push_back(shape);
}

/**
 * @brief Détermine si un point est occulté par un objet (calcul d'ombre).
 * @param point Le point d'impact à tester.
 * @return true si un objet bloque l'accès à la source lumineuse.
 */
bool Scene::isInShadow(const Vector3f& point) {
    // Vecteur allant du point vers la lumière
    Vector3f lightDir = source.getOrigin() - point;
    float distanceToLight = lightDir.length();
    Vector3f direction = lightDir.normalize();

    // Rayon d'ombre : décalé d'EPSILON pour ne pas se toucher soi-même
    Ray3f shadowRay(point + (direction * EPSILON), direction);
    HitInfo tempInfo;
    
    // Test d'intersection avec tous les objets de la scène
    for (const auto& shape : shapes) {
        if (shape->is_hit(shadowRay, 0.0f, distanceToLight, tempInfo)) {
            return true; // Un objet bloque le rayon
        }
    }
    return false;
}

/**
 * @brief Calcule l'éclairage local (Modèle diffus de Lambert).
 * @param hit Informations sur l'impact (normale, point, matériau).
 * @return Couleur finale du point après éclairage et ombres.
 */
Vector3f Scene::calculateLighting(const HitInfo& hit) {
    // Lumière ambiante minimale (pour ne pas avoir de zones 100% noires)
    Vector3f ambient(0.1f, 0.1f, 0.1f);
    
    // Si le point est dans l'ombre, seule la lumière ambiante s'applique
    if (isInShadow(hit.point)) {
        return Vector3f(hit.material.getR(), hit.material.getG(), hit.material.getB()) * ambient;
    }

    // Calcul de l'intensité diffuse : produit scalaire entre normale et lumière
    Vector3f lightDir = (source.getOrigin() - hit.point).normalize();
    float diff = std::max(0.0f, hit.normal.dot(lightDir));
    
    Vector3f objectColor(hit.material.getR(), hit.material.getG(), hit.material.getB());
    
    // Formule : Objet * (Ambiance + Intensité Diffuse)
    return objectColor * (ambient + Vector3f(1.0f, 1.0f, 1.0f) * diff);
}

/**
 * @brief Fonction récursive de lancer de rayon pour gérer les réflexions.
 * @param ray Le rayon à tracer.
 * @param depth Limite de récursion (nombre de rebonds restants).
 * @return Couleur accumulée le long du trajet du rayon.
 */
Vector3f Scene::traceRay(const Ray3f& ray, int depth) {
    // Arrêt si la limite de rebonds est atteinte
    if (depth <= 0) {
        return Vector3f(0.0f, 0.0f, 0.0f);
    }

    HitInfo closestHit;
    bool hitAnything = false;
    float closestSoFar = INFINITY_FLT;

    // Trouve l'objet le plus proche sur la trajectoire
    for (Shape* shape : shapes) {
        HitInfo tempHit;
        if (shape->is_hit(ray, EPSILON, closestSoFar, tempHit)) {
            hitAnything = true;
            closestSoFar = tempHit.distance;
            closestHit = tempHit;
        }
    }

    // Si aucune intersection, renvoie une couleur de fond (ciel bleu foncé)
    if (!hitAnything) {
        return Vector3f(0.1f, 0.1f, 0.2f);
    }

    // Calcul de la lumière locale (diffus + ombres)
    Vector3f localColor = calculateLighting(closestHit);

    // Gestion de la réflexion miroir (si le matériau est brillant)
    float reflectivity = closestHit.material.getShininess();
    if (reflectivity > 0.0f) {
        Vector3f incidentDir = ray.getDirection().normalize();
        Vector3f normal = closestHit.normal;
        
        // Formule de réflexion vectorielle : R = D - 2(D.N)N
        Vector3f reflectDir = incidentDir - normal * (2.0f * incidentDir.dot(normal));
        Ray3f reflectedRay(closestHit.point + (normal * EPSILON), reflectDir.normalize());

        // Appel récursif pour obtenir la couleur réfléchie
        Vector3f reflectedColor = traceRay(reflectedRay, depth - 1);

        // Mélange proportionnel entre la couleur propre de l'objet et le reflet
        return (localColor * (1.0f - reflectivity)) + (reflectedColor * reflectivity);
    }

    return localColor;
}

/**
 * @brief Boucle principale de rendu : parcourt chaque pixel de l'image.
 * @param width Largeur de l'image.
 * @param height Hauteur de l'image.
 * @param filename Nom du fichier PPM de sortie.
 * @param imageBuffer Buffer de pixels pour l'affichage SDL.
 */
void Scene::render(int width, int height, const std::string& filename, std::vector<Vector3f>& imageBuffer) {
    imageBuffer.resize(width * height);
    float aspectRatio = (float)width / (float)height;

    std::cout << "Lancement du rendu..." << std::endl;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            // Calcul des coordonnées normalisées de l'écran [-1, 1]
            float u = (2.0f * (float)(x + 0.5f) / (float)width) - 1.0f;
            float v = 1.0f - (2.0f * (float)(y + 0.5f) / (float)height);

            // Création du rayon passant par le centre du pixel
            Ray3f ray = camera.getRay(u, v, aspectRatio);

            // Lancement du trajet lumineux (5 rebonds max)
            Vector3f pixelColor = traceRay(ray, 5);

            // Limitation des valeurs (clamping) pour éviter les couleurs invalides
            float r = std::min(1.0f, std::max(0.0f, pixelColor.getX()));
            float g = std::min(1.0f, std::max(0.0f, pixelColor.getY()));
            float b = std::min(1.0f, std::max(0.0f, pixelColor.getZ()));

            imageBuffer[y * width + x] = Vector3f(r, g, b);
        }
    }
    
    // Sauvegarde de l'image au format PPM
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "P3\n" << width << " " << height << "\n255\n";
        for (const auto& pixel : imageBuffer) {
            int ir = static_cast<int>(pixel.getX() * 255.99f);
            int ig = static_cast<int>(pixel.getY() * 255.99f);
            int ib = static_cast<int>(pixel.getZ() * 255.99f);
            file << ir << " " << ig << " " << ib << "\n";
        }
        file.close();
        std::cout << "Rendu terminé et sauvegardé." << std::endl;
    }
}