//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_RECT2_H
#define GOLFENGINE_RECT2_H


#include <vector>
#include "Vector2.h"

struct Rect2 {
    Vector2 position;
    Vector2 size;
    Rect2() : position{Vector2{}}, size{Vector2{}}{}
    Rect2(const Vector2& p, const Vector2& s) : position{p}, size{s}{}
};


#endif //GOLFENGINE_RECT2_H
