//
// Created by olafv on 11/24/2022.
//
#include "Text.h"
#include "Services/Singletons/RenderSingleton.h"
#include <memory>



Text::Text(Vector2 pos, float rotation, std::string text, size_t fontSize, Color color, std::string filePath,
           Alignment alignment, bool isButtonPart) : _renderShape {TextRenderShape(pos, rotation, text, fontSize, color, filePath)} {
    _position = pos;
    _alignment = alignment;
    if(!isButtonPart){
        GolfEngine::Services::Render::getService()->addDrawable(*this);
    }

}


RenderShape& Text::getRenderShape() {
    return _renderShape;
}

