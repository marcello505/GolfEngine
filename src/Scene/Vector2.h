//
// Created by olafv on 11/02/2022.
// Created by jaaps on 11/02/2022.
//

#ifndef GOLFENGINE_VECTOR2_H
#define GOLFENGINE_VECTOR2_H
struct Vector2
{
    float x;
    float y;
    Vector2() : x{0}, y{0}{}
    Vector2(float X, float Y) : x{X}, y{Y}{}
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
    Vector2 operator*(const Vector2& b) const{
        return {
            x * b.x,
            y * b.y
        };
    }
};
#endif //GOLFENGINE_VECTOR2_H
