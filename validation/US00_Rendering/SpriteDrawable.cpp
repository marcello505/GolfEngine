//
// Created by conner on 11/9/2022.
//

#include "SpriteDrawable.h"

SpriteDrawable::SpriteDrawable(const std::string& path, Vector2 pixelScale, Rect2 imageSource, Transform transform, Color color) : _transform{transform} {
    _renderShape = std::make_unique<SpriteRenderShape>(path, transform.position, pixelScale, imageSource, Vector2(), _transform.rotation, color);
}

RenderShape* SpriteDrawable::getRenderShape() {
    _renderShape->applyTransform(_transform);
    return _renderShape.get();
}

void SpriteDrawable::rotate(float amount) {
    _transform.rotation += amount;
}

void SpriteDrawable::scale(float amount) {
    _transform.scale.x += amount;
    _transform.scale.y += amount;
}
