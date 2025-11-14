#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"

class Camera {
private:
    /* Position de la caméra dans l'espace */
    Vector3f position;
    /* Direction vers laquel on regarde*/
    Vector3f direction;


public:
    /* Constructeur par défaut de la caméra, on la place à l'origine du reprère et on la fait pointer vers l'avant selon la règle de la main droite */
    Camera(Vector3f position_value = Vector3f(0.0f, 0.0f, 0.0f), Vector3f direction_value = Vector3f(0.0f, 0.0f, -1.0f));
    /* getteur pour la position */
    Vector3f getPosition() const;
    /* getteur pour la direction */
    Vector3f getDirection() const;
};

#endif
 