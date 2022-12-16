//
// Created by marcello on 12/16/22.
//

#include <exception>
#include <stdexcept>
#include "GraphRenderShape.h"

RenderShapeType GraphRenderShape::getType() {
    return RenderShapeType::GraphRenderShape;
}

void GraphRenderShape::applyTransform(const Transform& transform) {
    throw std::logic_error("ApplyTransform is intentionally not implemented");
}
