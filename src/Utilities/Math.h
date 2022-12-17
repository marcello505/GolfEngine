//
// Created by marcello on 11/29/22.
//

#ifndef GOLFENGINE_MATH_H
#define GOLFENGINE_MATH_H


//Forward decleration
class Vector2;

namespace GolfEngine::Utilities::Math{
    /// Degrees to Radians
    /// \param deg degrees
    /// \return given degrees converted to radians
    float deg2Rad(float deg);
    /// Radians to Degrees
    /// \param rad radians
    /// \return given radians converted to degrees
    float rad2Deg(float rad);

    float atan2(const Vector2& vec);

    /// Round the number to the nearest multiple, for example.
    /// NUM     MULT    RESULT
    /// 12      5       10
    /// 13      5       15
    /// 149     10      150
    /// \param number the number to round up
    /// \param multiple the multiple to round up or down to
    /// \return A rounded up or down number based on the multiple
    int roundToNearestMultiple(int number, int multiple);
}


#endif //GOLFENGINE_MATH_H
