//
// Created by conner on 11/2/2022.
//

#include "LineRenderShape.h"

LineRenderShape::LineRenderShape() {
}

RenderShapeType LineRenderShape::getType() {
    return RenderShapeType::LineShape;
}

void LineRenderShape::applyTransform(const Transform& transform) {
}
