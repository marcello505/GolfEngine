//
// Created by conner on 11/2/2022.
//

#include "SpriteRenderShape.h"

#include <utility>

SpriteRenderShape::SpriteRenderShape(std::string path, Vector2 position, float rotation, Vector2 pixelScale, Rect2 imageSource, Vector2 pivotPoint, Color color)
    : _position{position},_initialPosition{position} , _path{std::move(path)}, _imageSource{imageSource}, _rotation{rotation}, _color{color},
    _initialPixelScale{pixelScale}, _pivotPoint{pivotPoint}, _pixelScale{pixelScale}
{
}

RenderShapeType SpriteRenderShape::getType() {
    return RenderShapeType::SpriteShape;
}

void SpriteRenderShape::applyTransform(const Transform& transform) {
    _position.x = _initialPosition.x + transform.position.x;
    _position.y = _initialPosition.y + transform.position.y;
    _rotation = transform.rotation;
    if(_initialPixelScale.x != 0)
        _pixelScale.x = (1/_initialPixelScale.x) * transform.scale.x;
    if(_initialPixelScale.y != 0)
        _pixelScale.y = (1/_initialPixelScale.y) * transform.scale.y;
}

float SpriteRenderShape::rotation() const {
    return _rotation;
}

std::string SpriteRenderShape::path() const {
    return _path;
}

Rect2 SpriteRenderShape::imageSource() const {
    return _imageSource;
}

Color SpriteRenderShape::color() const {
    return _color;
}

Vector2 SpriteRenderShape::pivotPoint() const {
    return _pivotPoint;
}

Vector2 SpriteRenderShape::position() const {
    return _position;
}

Vector2 SpriteRenderShape::pixelScale() const {
    return _pixelScale;
}
