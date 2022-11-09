//
// Created by conner on 11/9/2022.
//

#include "SpriteDrawable.h"

SpriteDrawable::SpriteDrawable(Rect2 rect, const std::string& path, Rect2 imageSource, Transform transform, Color color) : _transform{transform} {
    _renderShape = std::make_unique<SpriteRenderShape>(rect, path, imageSource, _transform.rotation, color);
}

RenderShape* SpriteDrawable::getRenderShape() {
    _renderShape->applyTransform(_transform);
    return _renderShape.get();
}

void SpriteDrawable::rotate(float amount) {
    _transform.rotation += amount;
}
