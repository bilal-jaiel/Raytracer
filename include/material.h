#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
private:
    float r, g, b;
    float shininess;


public:
    /* Constructeur par défaut du matériaux, par défaut blanc et à moitié translucide */
    Material(float r_value = 1.0f, float g_value = 1.0f, float b_value = 1.0f, float shininess_value = 0.5f);
    /* Guetteur de la première composante de la couleur RGB */
    float getR() const;
    /* Guetteur de la deuxième composante de la couleur RGB */
    float getG() const;
    /* Guetteur de la troisième composante de la couleur RGB */
    float getB() const;
    /* Guetteur de la translucidité de matériaux */
    float getShininess() const;
};

#endif