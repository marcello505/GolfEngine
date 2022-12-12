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
}


#endif //GOLFENGINE_MATH_H
