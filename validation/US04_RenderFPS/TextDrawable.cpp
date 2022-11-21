//
// Created by Lucas on 17-11-2022.
//

#include "TextDrawable.h"

TextDrawable::TextDrawable(Vector2 pos, Transform transform, std::string text, size_t fontSize, Color color, std::string filePath, GameLoop& gl) : _transform{transform} , _gameLoop{gl} {
    _renderShape = std::make_unique<TextRenderShape>(pos, transform.rotation, text, fontSize, color, filePath);
}

RenderShape *TextDrawable::getRenderShape() {
    _renderShape->applyTransform(_transform);
    std::string fps =   std::to_string(_gameLoop.time->getRenderFps());
    _renderShape->setText(fps);

    return _renderShape.get();
}

void TextDrawable::rotate(float amount) {
    _transform.rotation += amount;
}

void TextDrawable::move(int x, int y) {
    _transform.position.x += x;
    _transform.position.y += y;
}

void TextDrawable::setText(std::string text) {
    _renderShape->setText(text);

}

