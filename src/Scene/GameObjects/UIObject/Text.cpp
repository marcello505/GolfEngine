//
// Created by olafv on 11/24/2022.
//
#include "Text.h"
#include <memory>



Text::Text(Vector2 pos, float rotation, std::string text, size_t fontSize, Color color, std::string filePath,
           Alignment alignment) {
    _alignment = alignment;
    //setup rendershape
    _renderShape = std::make_unique<TextRenderShape>(pos, rotation, text, fontSize, color, filePath);
}


RenderShape* Text::getRenderShape() {
    return _renderShape.get();
}

