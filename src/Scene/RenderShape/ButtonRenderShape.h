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

namespace GolfEngine::Scene::Render {
    class ButtonRenderShape : public RenderShape {
    public:
        /// RenderShape used to render a button
        /// \param rectRenderShape rectangle to render button outline
        /// \param textRenderShape text to render text inside button
        /// \param alignment alignment of button
        ButtonRenderShape(RectRenderShape *rectRenderShape, TextRenderShape *textRenderShape, UI::Alignment alignment);
        UI::Alignment _textAlign;
        RenderShapeType getType() override;
        void applyTransform(const Transform &transform) override;

        std::unique_ptr<RectRenderShape> _rectRenderShape{};
        std::unique_ptr<TextRenderShape> _textRenderShape{};
    private:
    };
}


#endif //GOLFENGINE_BUTTONRENDERSHAPE_H
