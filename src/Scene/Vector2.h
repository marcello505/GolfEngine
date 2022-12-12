//
// Created by olafv on 11/02/2022.
// Created by jaaps on 11/02/2022.
//

#ifndef GOLFENGINE_VECTOR2_H
#define GOLFENGINE_VECTOR2_H

#include <cmath>
#include "Utilities/Math.h"

struct Vector2
{
    //Fields
    float x;
    float y;

    //Constructors
    Vector2(float X, float Y) : x{X}, y{Y}{}
    Vector2() : Vector2(0.0f, 0.0f){}

    //Methods

    /// Return the magnitude of the vector as a float.
    /// \return magnitude
    [[nodiscard]] float magnitude() const{
        // Info over formula's:
        // https://www.khanacademy.org/computing/computer-programming/programming-natural-simulations/programming-vectors/a/vector-magnitude-normalization
        return sqrtf(x * x + y * y);
    }

    /// Calculated a normalized vector using the current values and return it.
    /// \return A copy of the Vector with normalized fields
    [[nodiscard]] Vector2 normalized() const{
        // Info over formula's:
        // https://www.khanacademy.org/computing/computer-programming/programming-natural-simulations/programming-vectors/a/vector-magnitude-normalization
        Vector2 result {x, y};
        float mag = result.magnitude();
        if(mag > 0){
            result.x /= mag;
            result.y /= mag;
        }

        return result;
    }

    /// Returns a normalized vector from the current vector towards the given vector.
    /// Essentially does b - this, which is then normalized.
    /// \param b The point which should be calculated
    /// \return A normalized vector pointing towards b from the position of a
    [[nodiscard]] Vector2 directionTo(const Vector2& b) const{
        return (b - *this).normalized();
    }

    /// Returns the angle from this vector to the given vector in radians
    /// \param b The other vector
    /// \return Angle in radians
    [[nodiscard]] float angleToRadians(const Vector2& b) const{
        return GolfEngine::Utilities::Math::atan2(directionTo(b));
    }

    /// Returns the angle from this vector to the given vector in degrees
    /// \param b The other vector
    /// \return Angle in degrees
    [[nodiscard]] float angleToDegrees(const Vector2& b) const{
        return GolfEngine::Utilities::Math::rad2Deg(angleToRadians(b));
    }

    //Operator Overloads
    Vector2 operator+(Vector2& other) const{return {this->x + other.x, this->y + other.y};}
    Vector2& operator+=(const Vector2& b){
        x += b.x;
        y += b.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& b){
        x -= b.x;
        y -= b.y;
        return *this;
    }
    Vector2& operator*=(const Vector2& b){
        x *= b.x;
        y *= b.y;
        return *this;
    }
    Vector2 operator-(const Vector2& b) const{
        return{
            x - b.x,
            y - b.y
        };
    }
    Vector2 operator+(const Vector2& b) const{
        return{
                x + b.x,
                y + b.y
        };
    }
    Vector2 operator*(const Vector2& b) const{
        return {
            x * b.x,
            y * b.y
        };
    }

    Vector2 operator*(float b) const{
        return {
            x * b,
            y * b
        };
    }

    Vector2 operator/(const Vector2& b) const{
        return {
                x / b.x,
                y / b.y
        };
    }
};
#endif //GOLFENGINE_VECTOR2_H
