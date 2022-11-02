//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RECTRENDERSHAPE_H
#define SPC_PROJECT_RECTRENDERSHAPE_H

#include "RenderShape.h"
#include "../Rect2.h"
#include "../Color.h"

class RectRenderShape : public RenderShape {
public:
    RectRenderShape();
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
private:
    Rect2 _rect;
    float _rotation;
    Color _color;
};


#endif //SPC_PROJECT_RECTRENDERSHAPE_H
