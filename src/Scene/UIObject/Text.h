//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_TEXT_H
#define GOLFENGINE_TEXT_H


#include <string>
#include "Alignment.h"

//TODO replace this wit correct Color include
class Color;

class Text {
private:
    std::string _text;
    std::string _font;
    int _size;
    Alignment _alignment;
    Color _color;

};


#endif //GOLFENGINE_TEXT_H
