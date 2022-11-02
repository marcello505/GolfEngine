//
// Created by conner on 11/2/2022.
//

#include "RectRenderShape.h"

RectRenderShape::RectRenderShape() {
}

RenderShapeType RectRenderShape::getType() {
    return RenderShapeType::RectShape;
}

void RenderShape::applyTransform(const Transform &transform) {
}
