//
// Created by olafv on 11/24/2022.
//
#include "Text.h"
#include <memory>



Text::Text(Vector2 pos, float rotation, std::string text, size_t fontSize, Color color, std::string filePath,
           Alignment alignment) : _renderShape {TextRenderShape(pos, rotation, text, fontSize, color, filePath)} {
    _alignment = alignment;
}


RenderShape& Text::getRenderShape() {
    return _renderShape;
}

