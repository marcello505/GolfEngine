//
// Created by olafv on 11/23/2022.
//

#ifndef GOLFENGINE_BUTTONRENDERSHAPE_H
#define GOLFENGINE_BUTTONRENDERSHAPE_H
#include "RectRenderShape.h"
#include "TextRenderShape.h"
#include <memory>
#include "RenderShape.h"

class ButtonRenderShape : public RenderShape{
public:
    ButtonRenderShape(RectRenderShape* rectRenderShape, TextRenderShape* textRenderShape);

    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
    std::shared_ptr<RectRenderShape> _rectRenderShape;
    std::shared_ptr<TextRenderShape> _textRenderShape;
private:
};


#endif //GOLFENGINE_BUTTONRENDERSHAPE_H
