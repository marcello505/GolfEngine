//
// Created by conner on 11/2/2022.
//

#include "CircleRenderShape.h"

CircleRenderShape::CircleRenderShape(Vector2 position, float radius, Color color):
_position{position}, _radius{radius}, _initialRadius{radius}, _initialPosition{position}, _color{color}
{

}

RenderShapeType CircleRenderShape::getType() {
    return RenderShapeType::CircleShape;
}

void CircleRenderShape::applyTransform(const Transform &transform) {
    _position.x = _initialPosition.x + transform.position.x;
    _position.y = _initialPosition.y + transform.position.y;
    _radius =  _initialRadius * transform.scale.x;
}

Vector2 CircleRenderShape::position() const {
    return _position;
}

float CircleRenderShape::radius() const {
    return _radius;
}

Color CircleRenderShape::color() const {
    return _color;
}




