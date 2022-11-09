//
// Created by conner on 11/7/2022.
//

#include "RectDrawable.h"

RectDrawable::RectDrawable(Rect2 rect, Transform transform, Color color) : _transform{transform} {
    _renderShape = std::make_unique<RectRenderShape>(rect, _transform.rotation, color);
}

RenderShape* RectDrawable::getRenderShape() {
    _renderShape->applyTransform(_transform);
    return _renderShape.get();
}

void RectDrawable::rotate(float amount) {
    _transform.rotation += amount;
}
