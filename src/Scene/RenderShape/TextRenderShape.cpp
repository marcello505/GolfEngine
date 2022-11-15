//
// Created by Lucas on 15-11-2022.
//

#include "TextRenderShape.h"

TextRenderShape::TextRenderShape(Vector2 position, std::string text, int, Color color):
    _position{position}, _text{text}, _color{color}
{
}

RenderShapeType TextRenderShape::getType() {
    return RenderShapeType::TextRenderShape;
}

void TextRenderShape::applyTransform(const Transform &transform) {
    // no transforms
}

Vector2 TextRenderShape::position() const {
    return _position;
}

std::string TextRenderShape::text() const {
    return _text;
}

Color TextRenderShape::color() const {
    return _color;
}
