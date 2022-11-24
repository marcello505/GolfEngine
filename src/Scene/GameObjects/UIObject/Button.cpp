//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"

#include <utility>
#include "../../../../validation/US00_Rendering/RectDrawable.h"


[[maybe_unused]] bool Button::interactable() const {
    return false;
}

Button::Button(ButtonRenderShape* buttonRenderShape) {
    _buttonRenderShape = std::make_unique<ButtonRenderShape>(buttonRenderShape->_rectRenderShape.get(),
                                                             buttonRenderShape->_textRenderShape.get());
}

RenderShape *Button::getRenderShape() {
    return _buttonRenderShape.get();
}


