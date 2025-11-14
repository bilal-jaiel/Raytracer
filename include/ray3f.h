#ifndef RAY3F_H
#define RAY3F_H

#include "vector3f.h"

class Ray3f {
private:
    /* Le rayon est constitué d'une origine */
    Vector3f origin;
    /* Le rayon est constitué d'une direction */
    Vector3f direction;


public:
    /* Constructeur par défaut du vecteur 3D */
    Ray3f(Vector3f origin_value = Vector3f(0.0f, 0.0f, 0.0f), Vector3f direction_value = Vector3f(0.0f, 0.0f, -1.0f));
    /* Guetteur de l'origine du vecteur */
    Vector3f getOrigin() const;
    /* Guetteur de la direction du vecteur */
    Vector3f getDirection() const;
};

#endif