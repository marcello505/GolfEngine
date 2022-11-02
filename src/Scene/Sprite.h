//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_SPRITE_H
#define GOLFENGINE_SPRITE_H


#include <string>
#include "Color.h"
#include "Rect2.h"

struct Sprite {
    std::string sprite;
    Rect2 imageSource;
    Color color;
    bool flipX;
    bool flipY;
    int sortingLayer;
    int orderInLayer;
};


#endif //GOLFENGINE_SPRITE_H
