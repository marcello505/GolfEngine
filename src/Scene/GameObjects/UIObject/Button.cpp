//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"

#include <utility>
#include <Scene/GameObjects/UIObject/Alignment.h>


[[maybe_unused]] bool Button::interactable() const {
    return false;
}

Button::Button(int width, int height, Vector2 position, bool interactable, Text* text) {
    _width = width;
    _height = height;
    _position = position;
    _interactable = interactable;

    _text = std::unique_ptr<Text>{text};
    setShape();


}

RenderShape *Button::getRenderShape() {
    return _buttonRenderShape.get();
}


void Button::setShape() {
    auto* renderShape  = new RectRenderShape(Rect2(_position, Vector2(_width, _height)),
                                             0,
                                             Vector2((_position.x /2) ,(_position.y / 2) ),
                                             Color(255,255,255,255));

    _text->_renderShape->setPosition(Vector2(renderShape->pivotPoint().x + (_width / 2.7), renderShape->pivotPoint().y + (_height / 2.7)));

    auto* renderButton = new ButtonRenderShape(renderShape, _text->_renderShape.get());
    _buttonRenderShape = std::make_unique<ButtonRenderShape>(renderButton->_rectRenderShape.get(),
                                                             renderButton->_textRenderShape.get());
}


