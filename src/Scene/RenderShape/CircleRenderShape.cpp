//
// Created by conner on 11/2/2022.
//

#include "CircleRenderShape.h"

CircleRenderShape::CircleRenderShape() {
}

RenderShapeType CircleRenderShape::getType() {
    return RenderShapeType::CircleShape;
}

void CircleRenderShape::applyTransform(const Transform &transform) {
}
