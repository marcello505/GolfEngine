//
// Created by conner on 11/2/2022.
//

#include "LineRenderShape.h"

LineRenderShape::LineRenderShape(Vector2 posA, Vector2 posB, Color color)
    : _positionA{posA}, _positionB{posB}, _color{color}
{
}

RenderShapeType LineRenderShape::getType() {
    return RenderShapeType::LineShape;
}

void LineRenderShape::applyTransform(const Transform& transform) {
    // Line does not get affected by Transform
}

Vector2 LineRenderShape::positionA() const {
    return _positionA;
}

Vector2 LineRenderShape::positionB() const {
    return _positionB;
}

Color LineRenderShape::color() const {
    return _color;
}
