//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_COLLIDER_H
#define GOLFENGINE_COLLIDER_H
#include "Component.h"
#include "Drawable.h"

enum class ColliderShapes{
    Circle,
    Box
};

class Collider : public Component, public Drawable {
public:
    virtual ColliderShapes getColliderShape() = 0;
};


#endif //GOLFENGINE_COLLIDER_H
