//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_CIRCLERENDERSHAPE_H
#define SPC_PROJECT_CIRCLERENDERSHAPE_H

#include "RenderShape.h"
// TODO replace with include
class Vector2;
class Color;

class CircleRenderShape {
public:
    CircleRenderShape();
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
private:
    vector2 _position;
    float _radius;
    Color _color;
};


#endif //SPC_PROJECT_CIRCLERENDERSHAPE_H
