//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_SPRITE_H
#define GOLFENGINE_SPRITE_H


#include <string>
#include "Color.h"
#include "Rect2.h"

struct Sprite {
private:
    std::string _sprite;
    Rect2 _imageSource;
    Color _color;
    bool _flipX;
    bool _flipY;
    int _sortingLayer;
    int _orderInLayer;
};


#endif //GOLFENGINE_SPRITE_H
