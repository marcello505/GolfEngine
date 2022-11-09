//
// Created by conner on 11/2/2022.
//

#include "SpriteRenderShape.h"

#include <utility>

SpriteRenderShape::SpriteRenderShape(Rect2 rect, std::string path, Rect2 imageSource, float rotation, Color color)
    : _rect{rect}, _path{std::move(path)}, _imageSource{imageSource}, _rotation{rotation}, _color{color}, _initialSize{rect.size}
{
}

RenderShapeType SpriteRenderShape::getType() {
    return RenderShapeType::SpriteShape;
}

void SpriteRenderShape::applyTransform(const Transform& transform) {
    _rect.position = transform.position;
    _rotation = transform.rotation;
    _rect.size.x = _initialSize.x * transform.scale.x;
    _rect.size.y = _initialSize.y * transform.scale.y;
}

Rect2 SpriteRenderShape::rect() const {
    return _rect;
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
