//
// Created by Lucas on 15-11-2022.
//

#include "TextRenderShape.h"

TextRenderShape::TextRenderShape(Vector2 position, float rotation, std::string text, size_t fontSize , Color color, std::string filePath):
    _position{position}, _initialPosition(position), _rotation{rotation}, _text{text}, _fontSize{fontSize}, _color{color}, _filePath{filePath}
{
}

RenderShapeType TextRenderShape::getType() {
    return RenderShapeType::TextRenderShape;
}

void TextRenderShape::applyTransform(const Transform &transform) {
    _position.x = _initialPosition.x + transform.position.x;
    _position.y = _initialPosition.y + transform.position.y;
    _rotation = transform.rotation;
}

Vector2 TextRenderShape::position() const {
    return _position;
}

float TextRenderShape::rotation() const {
    return _rotation;
}

std::string TextRenderShape::text() const {
    return _text;
}

size_t TextRenderShape::fontSize() const {
    return _fontSize;
}

Color TextRenderShape::color() const {
    return _color;
}

std::string TextRenderShape::filePath() const {
    return _filePath;
}
