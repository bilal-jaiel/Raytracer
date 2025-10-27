#include "../include/ray3f.h"

Ray3f::Ray3f(Vector3f origin_value, Vector3f direction_value){
    origin = origin_value;
    direction = direction_value;
}

Vector3f Ray3f::getOrigin() const {
    return origin;
}

Vector3f Ray3f::getDirection() const {
    return direction;
}