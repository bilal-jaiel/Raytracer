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
#include <algorithm> // pour std::min, std::max

// Une petite constante pour éviter l'auto-intersection (acné)
const float EPSILON = 1e-4f;
const float INFINITY_FLT = std::numeric_limits<float>::max();

/**
 * @brief Constructeur de la scène.
 */
Scene::Scene(Camera camera_value, Ray3f source_value)
    : camera(camera_value), source(source_value) {
}

/**
 * @brief Destructeur.
 * Important : Nettoie la mémoire des objets alloués dynamiquement (new).
 */
Scene::~Scene() {
    for (Shape* s : shapes) {
        delete s;
    }
    shapes.clear();
}

/**
 * @brief Ajoute un objet à la scène.
 */
void Scene::addShape(Shape* shape) {
    shapes.push_back(shape);
}

/**
 * @brief Teste si un point est dans l'ombre.
 * 
 * Lance un rayon depuis le point vers la lumière. Si un objet bloque le chemin,
 * le point est dans l'ombre.
 */
bool Scene::isInShadow(const Vector3f& point) {
    // 1. Vecteur vers la lumière
    // On suppose que source.getOrigin() est la position ponctuelle de la lumière
    Vector3f lightDir = source.getOrigin() - point;
    float distanceToLight = lightDir.length();
    Vector3f direction = lightDir.normalize();

    // 2. Création du "rayon d'ombre"
    // On décale légèrement le point de départ pour ne pas se cogner soi-même (EPSILON)
    Ray3f shadowRay(point + (direction * EPSILON), direction);

    HitInfo tempInfo;
    
    // 3. Vérification des intersections
    for (const auto& shape : shapes) {
        // On cherche une collision entre 0 et la distance de la lumière
        if (shape->is_hit(shadowRay, 0.0f, distanceToLight, tempInfo)) {
            return true; // Un objet bloque la lumière
        }
    }
    return false;
}

/**
 * @brief Calcule l'éclairage local (Lambertian / Diffus).
 */
Vector3f Scene::calculateLighting(const HitInfo& hit) {
    // Couleur ambiante (base minimale de lumière)
    Vector3f ambient(0.1f, 0.1f, 0.1f);
    
    // Si le point est dans l'ombre, on ne renvoie que l'ambiance
    if (isInShadow(hit.point)) {
        // On multiplie la couleur de l'objet par l'ambiance
        return Vector3f(hit.material.getR(), hit.material.getG(), hit.material.getB()) * ambient;
    }

    // Calcul Diffus (Loi de Lambert)
    Vector3f lightDir = (source.getOrigin() - hit.point).normalize();
    
    // Produit scalaire entre la normale et la lumière
    // max(0, dot) empêche d'éclairer l'objet par l'arrière
    float diff = std::max(0.0f, hit.normal.dot(lightDir));
    
    // Couleur de l'objet
    Vector3f objectColor(hit.material.getR(), hit.material.getG(), hit.material.getB());
    
    // Formule finale : Couleur * (Ambiance + Intensité Diffuse)
    // On suppose une lumière blanche d'intensité 1.0
    Vector3f result = objectColor * (ambient + Vector3f(1.0f, 1.0f, 1.0f) * diff);

    return result;
}

/**
 * @brief Fonction récursive principale du lancer de rayon.
 */
Vector3f Scene::traceRay(const Ray3f& ray, int depth) {
    // 1. CONDITION D'ARRÊT (Sécurité pour la récursion)
    if (depth <= 0) {
        return Vector3f(0.0f, 0.0f, 0.0f); // Noir (on a atteint la limite de rebonds)
    }

    HitInfo closestHit;
    bool hitAnything = false;
    float closestSoFar = std::numeric_limits<float>::max();

    // 2. RECHERCHE DE L'INTERSECTION LA PLUS PROCHE
    for (Shape* shape : shapes) {
        HitInfo tempHit;
        // On utilise un petit epsilon (1e-4) pour éviter l'acné (auto-intersection)
        if (shape->is_hit(ray, 1e-4f, closestSoFar, tempHit)) {
            hitAnything = true;
            closestSoFar = tempHit.distance;
            closestHit = tempHit;
        }
    }

    // 3. SI LE RAYON NE TOUCHE RIEN
    if (!hitAnything) {
        return Vector3f(0.1f, 0.1f, 0.2f); // Couleur du "ciel" (bleu très foncé)
    }

    // 4. CALCUL DE LA LUMIÈRE LOCALE (Diffuse + Ombres)
    // On appelle la fonction calculateLighting que nous avons définie
    Vector3f localColor = calculateLighting(closestHit);

    // 5. GESTION DES RÉFLEXIONS (L'effet miroir)
    float reflectivity = closestHit.material.getShininess(); // Ton coefficient 0 à 1

    if (reflectivity > 0.0f) {
        // Calculer la direction du rebond : R = D - 2(D.N)N
        Vector3f incidentDir = ray.getDirection().normalize();
        Vector3f normal = closestHit.normal;
        
        Vector3f reflectDir = incidentDir - normal * (2.0f * incidentDir.dot(normal));
        
        // Créer le rayon réfléchi (on part du point d'impact)
        // Note : on décale un tout petit peu (epsilon) pour ne pas retoucher l'objet
        Ray3f reflectedRay(closestHit.point + (normal * 1e-4f), reflectDir.normalize());

        // APPEL RÉCURSIF : on va voir ce que le reflet touche
        Vector3f reflectedColor = traceRay(reflectedRay, depth - 1);

        // MÉLANGE : On combine la couleur de l'objet et celle du reflet
        // Exemple : si reflectivity = 0.2, on prend 80% de la couleur locale et 20% du reflet
        return (localColor * (1.0f - reflectivity)) + (reflectedColor * reflectivity);
    }

    // Si l'objet n'est pas réfléchi, on renvoie juste sa couleur éclairée
    return localColor;
}

/**
 * @brief Boucle principale de rendu.
 * Génère l'image pixel par pixel et sauvegarde en PPM.
 */
void Scene::render(int width, int height, const std::string& filename, std::vector<Vector3f>& imageBuffer) {
    imageBuffer.resize(width * height);
    float aspectRatio = (float)width / (float)height;

    std::cout << "Debut du rendu..." << std::endl;

    // Boucle sur chaque pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            // Conversion coordonnées pixel (x,y) vers coordonnées normalisées (u,v) de -1 à 1
            float u = (2.0f * (float)(x + 0.5f) / (float)width) - 1.0f;
            // On inverse Y car en image 0 est en haut, en 3D souvent en bas
            float v = 1.0f - (2.0f * (float)(y + 0.5f) / (float)height);

            // Génération du rayon
            Ray3f ray = camera.getRay(u, v, aspectRatio);

            // Lancer du rayon (Max 5 rebonds)
            Vector3f pixelColor = traceRay(ray, 5);

            // Stockage dans le buffer (pour SDL plus tard)
            // On clamp les valeurs entre 0 et 1 pour la sécurité
            float r = std::min(1.0f, std::max(0.0f, pixelColor.getX()));
            float g = std::min(1.0f, std::max(0.0f, pixelColor.getY()));
            float b = std::min(1.0f, std::max(0.0f, pixelColor.getZ()));

            imageBuffer[y * width + x] = Vector3f(r, g, b);
        }
    }
    
    std::cout << "Rendu termine. Sauvegarde dans " << filename << "..." << std::endl;

    // Sauvegarde au format PPM (Portable Pixel Map) - Format texte simple
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
        std::cout << "Sauvegarde terminee." << std::endl;
    } else {
        std::cerr << "Erreur: Impossible de creer le fichier " << filename << std::endl;
    }
}