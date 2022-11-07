//
// Created by conner on 11/2/2022.
//

#include "RectRenderShape.h"

RectRenderShape::RectRenderShape(Rect2 rect, float rotation, Color color)
    : _rect{rect}, _rotation{rotation}, _color{color}, _initialSize{rect.size}
{
}

RenderShapeType RectRenderShape::getType() {
    return RenderShapeType::RectShape;
}

Rect2 RectRenderShape::rect() const {
    return _rect;
}

float RectRenderShape::rotation() const {
    return _rotation;
}

Color RectRenderShape::color() const {
    return _color;
}

void RectRenderShape::applyTransform(const Transform& transform) {
    _rect.position = transform.position;
    _rotation = transform.rotation;
    _rect.size.x = _initialSize.x * transform.scale.x;
    _rect.size.y = _initialSize.y * transform.scale.y;
}
