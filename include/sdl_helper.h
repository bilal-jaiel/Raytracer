/**
 * @file sdl_helper.h
 * @brief Gestion de l'affichage via la bibliothèque SDL
 */
#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "vector3f.h"

class SdlHelper {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool is_initialized;

public:
    /**
     * @brief Constructeur : Initialise SDL et ouvre la fenêtre
     */
    SdlHelper(int w, int h, const std::string& title);

    /**
     * @brief Destructeur : Ferme la fenêtre et quitte SDL
     */
    ~SdlHelper();

    /**
     * @brief Dessine les pixels calculés à l'écran
     * @param buffer Le tableau de couleurs calculé par la scène
     */
    void draw(const std::vector<Vector3f>& buffer);

    /**
     * @brief Met en pause le programme tant qu'on ne ferme pas la fenêtre
     */
    void waitForExit();
};

#endif