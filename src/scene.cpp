/**
 * @file scene.cpp
 * @brief Implémentation de la classe Scene
 * @author Votre nom
 * @date 2025
 */

#include "../include/scene.h"
#include <SDL2.h>
#include <algorithm>
#include <cmath>
#include <limits>

// Variables globales SDL (encapsulées dans le fichier)
static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_renderer = nullptr;

Scene::Scene(Camera camera_value, const std::vector<Shape*>& shapes_values, Ray3f source_value) {
    camera = camera_value;
    shapes = shapes_values;
    source = source_value;
}

Camera Scene::getCamera() const {
    return camera;
}

const std::vector<Shape*>& Scene::getShapes() const {
    return shapes;
}

Ray3f Scene::getSource() const {
    return source;
}

bool Scene::initSDL(int width, int height, std::string filename) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur SDL_Init: %s", SDL_GetError());
        return false;
    }
    
    g_window = SDL_CreateWindow(
        filename.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
    
    if (!g_window) {
        SDL_Log("Erreur SDL_CreateWindow: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_renderer) {
        SDL_Log("Erreur SDL_CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return false;
    }
    
    return true;
}

void Scene::cleanupSDL() {
    if (g_renderer) SDL_DestroyRenderer(g_renderer);
    if (g_window) SDL_DestroyWindow(g_window);
    SDL_Quit();
}

Ray3f Scene::generateRay(int x, int y, int width, int height) {
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    float fov = 60.0f;
    float scale = std::tan(fov * 0.5f * M_PI / 180.0f);
    
    Vector3f cameraPos = camera.getPosition();
    Vector3f cameraDir = camera.getDirection().normalize();
    Vector3f cameraRight = cameraDir.cross(Vector3f(0.0f, 1.0f, 0.0f)).normalize();
    Vector3f cameraUp = cameraRight.cross(cameraDir);
    
    float px = (2.0f * (x + 0.5f) / width - 1.0f) * aspectRatio * scale;
    float py = (1.0f - 2.0f * (y + 0.5f) / height) * scale;
    Vector3f rayDir = (cameraDir + cameraRight * px + cameraUp * py).normalize();
    
    return Ray3f(cameraPos, rayDir);
}

bool Scene::isInShadow(const Vector3f& point, const Vector3f& lightPos) {
    Vector3f toLight = (lightPos - point).normalize();
    float distToLight = (lightPos - point).length();
    
    Ray3f shadowRay(point + toLight * 1e-4f, toLight);
    
    for (size_t i = 0; i < shapes.size(); ++i) {
        HitInfo shadowInfo;
        if (shapes[i]->is_hit(shadowRay, 0.001f, distToLight, shadowInfo)) {
            return true;
        }
    }
    
    return false;
}

float Scene::calculateLighting(const HitInfo& hit, const Vector3f& lightPos) {
    Vector3f toLight = (lightPos - hit.point).normalize();
    float diffuse = std::max(0.0f, hit.normal.dot(toLight));
    float ambient = 0.2f;
    
    if (isInShadow(hit.point, lightPos)) {
        return ambient;
    }
    
    return ambient + 0.8f * diffuse;
}

Vector3f Scene::traceRay(const Ray3f& ray, int depth) {
    const int MAX_DEPTH = 3;
    const Vector3f BG_COLOR(50.0f, 70.0f, 100.0f);
    
    if (depth >= MAX_DEPTH) {
        return BG_COLOR;
    }
    
    // Trouver l'intersection la plus proche
    HitInfo closestHit;
    float closestDist = std::numeric_limits<float>::max();
    bool hitAnything = false;
    
    for (size_t i = 0; i < shapes.size(); ++i) {
        HitInfo tempHit;
        if (shapes[i]->is_hit(ray, 0.001f, closestDist, tempHit)) {
            if (tempHit.distance < closestDist) {
                closestDist = tempHit.distance;
                closestHit = tempHit;
                hitAnything = true;
            }
        }
    }
    
    if (!hitAnything) {
        return BG_COLOR;
    }
    
    // Calculer la couleur de base avec éclairage
    Vector3f lightPos = source.getOrigin();
    float lighting = calculateLighting(closestHit, lightPos);
    
    Vector3f objectColor(
        closestHit.material.getR() * 255.0f,
        closestHit.material.getG() * 255.0f,
        closestHit.material.getB() * 255.0f
    );
    
    Vector3f finalColor = objectColor * lighting;
    
    // Gérer la réflexion
    float shininess = closestHit.material.getShininess();
    if (shininess > 0.01f) {
        Vector3f reflectedDir = ray.getDirection() - closestHit.normal * 
                                (2.0f * ray.getDirection().dot(closestHit.normal));
        Ray3f reflectedRay(closestHit.point + closestHit.normal * 1e-4f, 
                           reflectedDir.normalize());
        
        Vector3f reflectedColor = traceRay(reflectedRay, depth + 1);
        finalColor = finalColor * (1.0f - shininess) + reflectedColor * shininess;
    }
    
    // Clamper les valeurs
    return Vector3f(
        std::min(255.0f, std::max(0.0f, finalColor.getX())),
        std::min(255.0f, std::max(0.0f, finalColor.getY())),
        std::min(255.0f, std::max(0.0f, finalColor.getZ()))
    );
}

void Scene::render(int width, int height, std::string filename) {
    if (!initSDL(width, height, filename)) {
        return;
    }
    
    SDL_Log("Rendu en cours... %dx%d pixels", width, height);
    
    // Boucle de rendu pixel par pixel
    for (int y = 0; y < height; ++y) {
        if (y % 50 == 0) {
            SDL_Log("Progression: %.1f%%", (float)y / height * 100.0f);
        }
        
        for (int x = 0; x < width; ++x) {
            Ray3f ray = generateRay(x, y, width, height);
            Vector3f color = traceRay(ray, 0);
            
            SDL_SetRenderDrawColor(g_renderer, 
                static_cast<Uint8>(color.getX()),
                static_cast<Uint8>(color.getY()),
                static_cast<Uint8>(color.getZ()),
                255
            );
            SDL_RenderDrawPoint(g_renderer, x, y);
        }
    }
    
    SDL_Log("Rendu terminé !");
    SDL_RenderPresent(g_renderer);
    
    // Boucle d'événements
    bool quit = false;
    SDL_Event event;
    SDL_Log("Appuyez sur ESC ou fermez la fenêtre pour quitter");
    
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
        SDL_Delay(16);
    }
    
    cleanupSDL();
}