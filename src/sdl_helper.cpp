#include "../include/sdl_helper.h"
#include <iostream>
#include <algorithm> // pour std::min
#include <cmath>     // pour fmin

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

SdlHelper::~SdlHelper() {
    if (is_initialized) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void SdlHelper::draw(const std::vector<Vector3f>& buffer) {
    if (!is_initialized) return;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Index dans le tableau 1D
            int index = y * width + x;
            Vector3f color = buffer[index];

            // Conversion float (0.0-1.0) vers int (0-255)
            // On sature à 255 max pour éviter les bugs d'affichage
            int r = static_cast<int>(fmin(color.getX(), 1.0f) * 255);
            int g = static_cast<int>(fmin(color.getY(), 1.0f) * 255);
            int b = static_cast<int>(fmin(color.getZ(), 1.0f) * 255);

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);
}

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
        SDL_Delay(50); // Petite pause pour ne pas surchauffer le CPU
    }
}