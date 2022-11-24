//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_UIOBJECT_H
#define GOLFENGINE_UIOBJECT_H
#include "../GameObject.h"
#include "Scene/Components/Drawable.h"

class UIObject : public Drawable {
private:

    float _width;
    float _height;
};


#endif //GOLFENGINE_UIOBJECT_H
