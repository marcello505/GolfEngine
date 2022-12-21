//
// Created by olafv on 11/2/2022.
//

#ifndef GOLFENGINE_TRANSFORM_H
#define GOLFENGINE_TRANSFORM_H
#include "Vector2.h"

namespace GolfEngine::Scene {
    struct Transform {
        Vector2 position;
        float rotation;
        Vector2 scale;

        Transform() : position{Vector2(0, 0)}, rotation{0}, scale{Vector2(1, 1)} {}

        Transform(Vector2 p, float r, Vector2 s) : position{p}, rotation{r}, scale{s} {}
    };
}
#endif //GOLFENGINE_TRANSFORM_H
