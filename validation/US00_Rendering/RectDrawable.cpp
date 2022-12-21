//
// Created by conner on 11/7/2022.
//

#include "RectDrawable.h"

RectDrawable::RectDrawable(Rect2 rect, Transform transform, Vector2 pivotPoint, Color color) : _transform{transform},
    _renderShape{RectRenderShape(rect, transform.rotation, pivotPoint, color)}{
}

RenderShape& RectDrawable::getRenderShape() {
    _renderShape.applyTransform(_transform);
    return _renderShape;
}
void RectDrawable::setColor(Color color){
    _renderShape.setColor(color);
}

void RectDrawable::rotate(float amount) {
    _transform.rotation += amount;
}

void RectDrawable::scale(float amount) {
    _transform.scale.x += amount;
    _transform.scale.y += amount;
}
