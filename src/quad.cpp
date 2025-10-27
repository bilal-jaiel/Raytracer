#include "../include/quad.h"

Quad::Quad(Vector3f origin_value, Vector3f width_value, Vector3f height_value) {
    origin = origin_value;
    width = width_value;
    height = height_value;
}

Vector3f Quad::getOrigin() const {
    return origin;
}

Vector3f Quad::getWidth() const {
    return width;
}

Vector3f Quad::getHeight() const {
    return height;
}