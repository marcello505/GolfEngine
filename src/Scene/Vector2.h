//
// Created by olafv on 11/02/2022.
// Created by jaaps on 11/02/2022.
//

#ifndef GOLFENGINE_VECTOR2_H
#define GOLFENGINE_VECTOR2_H

#include <cmath>

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
    float magnitude() const{
        // Info over formula's:
        // https://www.khanacademy.org/computing/computer-programming/programming-natural-simulations/programming-vectors/a/vector-magnitude-normalization
        return sqrtf(x * x + y * y);
    }

    /// Calculated a normalized vector using the current values and return it.
    /// \return A copy of the Vector with normalized fields
    Vector2 normalized() const{
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
