#include <stdexcept>
#include "../include/material.h"

Material::Material(float r_value, float g_value, float b_value, float shininess_value) {
    if (r_value < 0 || r_value > 1 || g_value < 0 || g_value > 1 || b_value < 0 || b_value > 1) {
        throw std::invalid_argument("Les valeurs RGB doivent être normalisées (entre 0 et 1)");
    }
    if (shininess_value < 0 || shininess_value > 1) {
        throw std::invalid_argument("Le coefficient de réflexion (shininess) doit être compris entre 0 et 1");
    }

    r = r_value;
    g = g_value;
    b = b_value;

    shininess = shininess_value;

}