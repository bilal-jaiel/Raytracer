/**
 * @file sdl_helper.h
 * @brief Gestion de l'affichage graphique via la bibliotheque SDL2
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */
#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "vector3f.h"


/**
 * @class SdlHelper
 * @brief Interface simplifiée pour l'affichage du tampon de pixels.
 */
class SdlHelper {
private:
    SDL_Window* window;      ///Fenêtre d'affichage
    SDL_Renderer* renderer;  /// Moteur de rendu SDL
    int width;               /// Largeur de l'image
    int height;              /// Hauteur de l'image
    bool is_initialized;     /// État de l'initialisation

public:
    /**
     * @brief Initialise SDL, crée la fenêtre et le renderer.
     * @param w Largeur en pixels.
     * @param h Hauteur en pixels.
     * @param title Titre de la fenêtre.
     */
    SdlHelper(int w, int h, const std::string& title);

    /**
     * @brief Libere les ressources SDL et ferme la fenêtre.
     */
    ~SdlHelper();

    /**
     * @brief Convertit et affiche le tampon de couleurs à l'écran.
     * @param buffer Vecteur 1D de couleurs au format RGB.
     */
    void draw(const std::vector<Vector3f>& buffer);

    /**
     * @brief Gere la boucle d'événements jusqu'à la fermeture de la fenêtre.
     */
    void waitForExit();
};

#endif