//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_CIRCLERENDERSHAPE_H
#define SPC_PROJECT_CIRCLERENDERSHAPE_H

#include "RenderShape.h"
#include "../Vector2.h"
#include "../Color.h"

class CircleRenderShape : public RenderShape{
public:
    CircleRenderShape();
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
private:
    Vector2 _position;
    float _radius;
    Color _color;
};


#endif //SPC_PROJECT_CIRCLERENDERSHAPE_H
