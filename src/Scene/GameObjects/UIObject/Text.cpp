//
// Created by olafv on 11/24/2022.
//
#include "Text.h"
#include "Services/Singletons/RenderSingleton.h"
#include <memory>

namespace GolfEngine::Scene::UI {
    Text::Text(Vector2 pos, float rotation, const std::string& text, size_t fontSize, Color color, const std::string& filePath,
               Alignment alignment, bool isButtonPart) : _renderShape{
            Render::TextRenderShape(pos, rotation, text, fontSize, color, filePath)} {
        _position = pos;
        _alignment = alignment;
        if (!isButtonPart) {
            Services::Render::getService()->addDrawable(*this);
        }

    }


    Render::RenderShape &Text::getRenderShape() {
        return _renderShape;
    }

    Text::~Text() {
        if (Services::Render::hasService())
            Services::Render::getService()->removeDrawable(*this);
    }
}
