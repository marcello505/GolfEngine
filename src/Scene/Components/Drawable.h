//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_DRAWABLE_H
#define GOLFENGINE_DRAWABLE_H
#include "../RenderShape/RenderShape.h"
#include "Scene/GameObjects/GameObject.h"

class Drawable {
private:

public:
    virtual RenderShape* getRenderShape() = 0;

};


#endif //GOLFENGINE_DRAWABLE_H
