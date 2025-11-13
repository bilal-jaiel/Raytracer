#include "../include/shape.h"

Shape::Shape(){
    Material();
}

Shape::Shape(Material matter_value){
    matter = matter_value;
}

Material Shape::getMatter() const {
    return matter;
}

Ray3f Shape::reflect(const Ray3f& incident, const Vector3f& normal, const Vector3f& hitPoint) {
    // Formule de réflexion : R = D - 2(D·N)N
    // où D = direction incidente, N = normale
    
    Vector3f D = incident.getDirection();
    Vector3f R = D - normal * (2.0f * D.dot(normal));
    
    // Le nouveau rayon part du point d'intersection
    // On ajoute un petit epsilon pour éviter l'auto-intersection
    const float EPSILON = 1e-4f;
    Vector3f newOrigin = hitPoint + normal * EPSILON;
    
    return Ray3f(newOrigin, R.normalize());
}