//
// Created by conner on 11/2/2022.
//

#include "SpriteRenderShape.h"

SpriteRenderShape::SpriteRenderShape() {
}

RenderShapeType SpriteRenderShape::getType() {
    return RenderShapeType::SpriteShape;
}

void SpriteRenderShape::applyTransform(const Transform &transform) {
}
