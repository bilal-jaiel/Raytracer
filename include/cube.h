/**
 * @file cube.h
 * @brief Classe représentant un cube dans la scène 3D
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

#ifndef CUBE_H
#define CUBE_H

#include "shape.h"
#include "vector3f.h"
#include "quad.h"
#include <vector>

/**
 * @class Cube
 * @brief Un cube composé de 6 quadrilatères
 */
class Cube : public Shape {
private:
    Vector3f center;
    float size;
    std::vector<Quad*> faces;
    
    /**
     * @brief Crée les 6 faces du cube
     */
    void createFaces();

public:
    /**
     * @brief Constructeur du cube
     * @param center_value Centre du cube
     * @param size_value Taille du cube
     * @param mat Matériau du cube
     */
    Cube(Vector3f center_value, float size_value, const Material& mat);
    
    /**
     * @brief Destructeur - libère les faces
     */
    ~Cube();
    
    /**
     * @brief Accesseur pour le centre
     * @return Centre du cube
     */
    Vector3f getCenter() const;
    
    /**
     * @brief Accesseur pour la taille
     * @return Taille du cube
     */
    float getSize() const;
    
    /**
     * @brief Teste l'intersection avec un rayon
     * @param ray Le rayon à tester
     * @param t_min Distance minimum
     * @param t_max Distance maximum
     * @param info Structure à remplir si intersection
     * @return true si intersection trouvée
     */
    bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const override;
};

#endif