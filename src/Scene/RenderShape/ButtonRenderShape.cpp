//
// Created by olafv on 11/23/2022.
//

#include "ButtonRenderShape.h"

ButtonRenderShape::ButtonRenderShape(RectRenderShape* rectRenderShape, TextRenderShape* textRenderShape,
                                     Alignment textAlign){
    _rectRenderShape.reset(rectRenderShape);
    _textRenderShape.reset(textRenderShape);
    _textAlign = textAlign;
}

RenderShapeType ButtonRenderShape::getType() {
    return RenderShapeType::ButtonRenderShape;
}

void ButtonRenderShape::applyTransform(const Transform &transform) {
    // Line does not get affected by Transform
}


