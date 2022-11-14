//
// Created by conner on 11/7/2022.
//

#include "RectDrawable.h"

RectDrawable::RectDrawable(Rect2 rect, Transform transform, Vector2 pivotPoint, Color color) : _transform{transform} {
    _renderShape = std::make_unique<RectRenderShape>(rect, _transform.rotation, pivotPoint, color);
}

RenderShape* RectDrawable::getRenderShape() {
    _renderShape->applyTransform(_transform);
    return _renderShape.get();
}

void RectDrawable::rotate(float amount) {
    _transform.rotation += amount;
}

void RectDrawable::scale(float amount) {
    _transform.scale.x += amount;
    _transform.scale.y += amount;
}
