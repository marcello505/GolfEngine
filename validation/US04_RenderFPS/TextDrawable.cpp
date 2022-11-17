//
// Created by Lucas on 17-11-2022.
//

#include "TextDrawable.h"

TextDrawable::TextDrawable(Vector2 pos, Transform transform, std::string text, size_t fontSize, Color color, std::string filePath) : _transform{transform} {
    _renderShape = std::make_unique<TextRenderShape>(pos, transform.rotation, text, fontSize, color, filePath);
}

RenderShape *TextDrawable::getRenderShape() {
    _renderShape->applyTransform(_transform);
    return _renderShape.get();
}

void TextDrawable::rotate(float amount) {
    _transform.rotation += amount;
}

void TextDrawable::move(int x, int y) {
    _transform.position.x += x;
    _transform.position.y += y;
}

