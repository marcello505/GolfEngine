//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SPRITERENDERSHAPE_H
#define SPC_PROJECT_SPRITERENDERSHAPE_H

#include "RenderShape.h"
#include "../Rect2.h"
#include "../Color.h"

class SpriteRenderShape : public RenderShape {
public:
    SpriteRenderShape();
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
private:
    Rect2 _rect;
    float _rotation;
    std::string _path;
    Rect2 _imageSource;
    Color _color;
};


#endif //SPC_PROJECT_SPRITERENDERSHAPE_H
