#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
private:
    float r, g, b;
    float shininess;


public:
    Material(float r_value = 1.0f, float g_value = 1.0f, float b_value = 1.0f, float shininess_value = 0.5f);
    float getR() const;
    float getG() const;
    float getB() const;
    float getShininess() const;
};

#endif