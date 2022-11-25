//
// Created by conner on 11/7/2022.
//

#include "LineDrawable.h"

LineDrawable::LineDrawable(Vector2 posA, Vector2 posB, Color color) :
    _renderShape{LineRenderShape(posA, posB, color)} {
}

RenderShape& LineDrawable::getRenderShape() {
    _renderShape.applyTransform(_transform);
    return _renderShape;
}
