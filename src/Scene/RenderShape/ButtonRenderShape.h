//
// Created by olafv on 11/23/2022.
//

#ifndef GOLFENGINE_BUTTONRENDERSHAPE_H
#define GOLFENGINE_BUTTONRENDERSHAPE_H
#include "RectRenderShape.h"
#include "TextRenderShape.h"
#include <memory>
#include "RenderShape.h"
#include "Scene/GameObjects/UIObject/Alignment.h"

class ButtonRenderShape : public RenderShape{
public:
    ButtonRenderShape(RectRenderShape* rectRenderShape, TextRenderShape* textRenderShape, Alignment alignment);
    Alignment _textAlign;
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
    std::unique_ptr<RectRenderShape> _rectRenderShape {};
    std::unique_ptr<TextRenderShape> _textRenderShape {};
private:
};


#endif //GOLFENGINE_BUTTONRENDERSHAPE_H
