#ifndef QUAD_H
#define QUAD_H

#include "shape.h"  
#include "vector3f.h"

class Quad : public Shape {
private:
    Vector3f origin;
    Vector3f width;
    Vector3f height;


public:
    /* Constructeur par défaut du quadrilatère, par défaut à une distance de 5 par rapport à la caméra, d'une hateur et une largeur 2 */
    Quad(Vector3f origin_value = Vector3f(0.0f, 0.0f, -5.0f), 
         Vector3f width_value = Vector3f(2.0f, 0.0f, 0.0f), 
         Vector3f height_value = Vector3f(0.0f, 2.0f, 0.0f), 
         const Material& mat = Material());
    
    /* Guetteur pour l'origine de la forme (en son centre) */
    Vector3f getOrigin() const;
    /* Guetteur pour la largeur de la forme */
    Vector3f getWidth() const;
    /* Guetteur pour la hauteur de la forme */
    Vector3f getHeight() const;
    /* Fonction qui calcule le ou les points d'intersections entre le rayon et la forme s'ils existent */
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif