//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"

#include <utility>
#include "../../../../validation/US00_Rendering/RectDrawable.h"


[[maybe_unused]] bool Button::interactable() const {
    return false;
}

Button::Button(int width, int height, Vector2 position, bool interactable) {
    _width = width;
    _height = height;
    _position = position;
    _interactable = interactable;
}

RenderShape *Button::getRenderShape() {
    return _buttonRenderShape.get();
}

void Button::setShape(ButtonRenderShape* buttonRenderShape) {
    _buttonRenderShape = std::make_unique<ButtonRenderShape>(buttonRenderShape->_rectRenderShape.get(),
                                                             buttonRenderShape->_textRenderShape.get());
}


