#ifndef HIT_INFO_H
#define HIT_INFO_H

#include "vector3f.h"
#include "material.h"

struct HitInfo {
    float distance;
    Vector3f point;
    Vector3f normal;
    Material material;
};

#endif