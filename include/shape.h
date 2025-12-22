/**
 * @file shape.h
 * @brief Classe représentant les objets de la scène
 * @author Jaiel Bilâl, Kalaivaasan Balakumar
 * @date 2025
 */

 #ifndef SHAPE_H
#define SHAPE_H

#include "material.h"
#include "ray3f.h"
#include "hit_info.h"

/**
 * @class Shape
 * @brief Classe abstraite de base représentant tout objet géométrique visible dans la scène.
 *
 * Cette classe définit l'interface commune pour toutes les formes (sphères, quads, etc.),
 * notamment la gestion du matériau et la méthode virtuelle pure d'intersection.
 */
class Shape {
private:
    /**
     * @brief Le matériau composant la forme (couleur, propriétés de surface).
     */
    Material matter;


public:
    /**
     * @brief Destructeur virtuel par défaut.
     * Nécessaire pour permettre la destruction correcte des objets dérivés via un pointeur de base.
     */
    virtual ~Shape() = default;

    /**
     * @brief Constructeur par défaut.
     */
    Shape();

    /**
     * @brief Constructeur paramétré.
     * @param matter_value Le matériau à assigner à la forme.
     */
    Shape(Material matter_value);

    /**
     * @brief Méthode virtuelle pure pour tester l'intersection avec un rayon.
     *
     * Doit être implémentée par chaque forme spécifique (Sphère, Quad, etc.) pour définir
     * comment elle interagit avec les rayons lumineux.
     *
     * @param ray Le rayon lancé dans la scène.
     * @param t_min La distance minimale valide (permet d'éviter l'auto-intersection ou "shadow acne").
     * @param t_max La distance maximale valide pour l'intersection.
     * @param info Structure de sortie remplie avec les détails de la collision (point, normale, etc.) si elle a lieu.
     * @return true Si le rayon touche la forme dans l'intervalle donné.
     * @return false Sinon.
     */
    virtual bool is_hit(const Ray3f& ray, float t_min, float t_max, HitInfo& info) const = 0;

    /**
     * @brief Calcule le rayon réfléchi.
     *
     * Génère un nouveau rayon correspondant à la réflexion spéculaire du rayon incident
     * par rapport à la normale de la surface.
     *
     * @param incident Le rayon arrivant sur la surface.
     * @param normal La normale de la surface au point d'impact.
     * @param hitPoint Le point d'impact (deviendra l'origine du rayon réfléchi).
     * @return Ray3f Le nouveau rayon réfléchi.
     */
    Ray3f reflect(const Ray3f& incident, const Vector3f& normal, const Vector3f& hitPoint);
    
    /**
     * @brief Accesseur pour le matériau.
     * @return Material L'objet matériau associé à la forme.
     */
    Material getMatter() const;
};

#endif