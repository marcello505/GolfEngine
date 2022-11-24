//
// Created by olafv on 11/23/2022.
//

#include "ButtonRenderShape.h"

ButtonRenderShape::ButtonRenderShape(RectRenderShape* rectRenderShape, TextRenderShape* textRenderShape) {
    _rectRenderShape = std::unique_ptr<RectRenderShape>{rectRenderShape};
    _textRenderShape = std::unique_ptr<TextRenderShape>{textRenderShape};
}

RenderShapeType ButtonRenderShape::getType() {
    return RenderShapeType::ButtonRenderShape;
}

void ButtonRenderShape::applyTransform(const Transform &transform) {
    // Line does not get affected by Transform
}


