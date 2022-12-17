//
// Created by marcello on 11/29/22.
//

#include <cmath>

#include "Scene/Vector2.h"
#include "Math.h"

namespace GolfEngine::Utilities::Math{
    // Degrees to Radians
    float deg2Rad(float deg){
        return deg * M_PI / 180.0f;
    }

    // Radians to Degrees
    float rad2Deg(float rad){
        return 180.0f * rad / M_PI;
    }

    float atan2(const Vector2& vec) {
        float x = vec.x;
        float y = vec.y;
        return atan2f(y, x);
    }

    int roundToNearestMultiple(int number, int multiple) {
        return ((number + multiple / 2) / multiple) * multiple;
    }
}