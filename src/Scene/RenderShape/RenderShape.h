//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RENDERSHAPE_H
#define SPC_PROJECT_RENDERSHAPE_H

#include "RenderShapeType.h"
// TODO replace with include
class Transform;

class RenderShape{
public:
    virtual RenderShapeType getType() = 0;
    virtual void applyTransform(const Transform& transform) = 0;
};


#endif //SPC_PROJECT_RENDERSHAPE_H
