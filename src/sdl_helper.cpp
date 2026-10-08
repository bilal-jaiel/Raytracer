/**
 * @file sdl_helper.cpp
 * @brief Gestion de l'affichage graphique via la bibliothèque SDL2
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#include "../include/sdl_helper.h"
#include <iostream>
#include <algorithm>
#include <cmath>

/**
 * @brief Initialise la fenêtre et le moteur de rendu SDL.
 * @param w Largeur de la fenêtre.
 * @param h Hauteur de la fenêtre.
 * @param title Titre de la fenêtre.
 */
SdlHelper::SdlHelper(int w, int h, const std::string& title) 
    : width(w), height(h), is_initialized(false) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL Init: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(title.c_str(), 
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              width, height, SDL_WINDOW_SHOWN);
    
    if (!window) return;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    is_initialized = true;
}

/**
 * @brief Destructeur : libère les ressources SDL.
 */
SdlHelper::~SdlHelper() {
    if (is_initialized) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

/**
 * @brief Affiche le tampon de pixels à l'écran.
 * @param buffer Vecteur de couleurs (Vector3f) représentant l'image.
 */
void SdlHelper::draw(const std::vector<Vector3f>& buffer) {
    if (!is_initialized) return;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calcul de l'index linéaire dans le tampon de pixels
            int index = y * width + x;
            Vector3f color = buffer[index];

            // Conversion et saturation des composantes (0.0-1.0 vers 0-255)
            int r = static_cast<int>(fmin(color.getX(), 1.0f) * 255);
            int g = static_cast<int>(fmin(color.getY(), 1.0f) * 255);
            int b = static_cast<int>(fmin(color.getZ(), 1.0f) * 255);

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    // Mise à jour effective de la fenêtre
    SDL_RenderPresent(renderer);
}

/**
 * @brief Maintient la fenêtre ouverte jusqu'à la fermeture manuelle.
 */
void SdlHelper::waitForExit() {
    if (!is_initialized) return;

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_Delay(50); // Limite l'usage CPU
    }
}