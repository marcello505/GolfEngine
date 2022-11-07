//
// Created by olafv on 11/2/2022.
//

#ifndef GOLFENGINE_TRANSFORM_H
#define GOLFENGINE_TRANSFORM_H
#include <string>
#include "Vector2.h"

struct Transform {
    Vector2 position;
    float rotation;
    Vector2 scale;
    Transform() : position{Vector2(0,0)}, rotation{0}, scale{Vector2(0,0)}{}
    Transform(Vector2 p, float r, Vector2 s) : position{p}, rotation{0}, scale{s}{}
};
#endif //GOLFENGINE_TRANSFORM_H
