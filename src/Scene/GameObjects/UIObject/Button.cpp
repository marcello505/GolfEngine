//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"

#include <utility>
#include <Scene/GameObjects/UIObject/Alignment.h>


[[maybe_unused]] bool Button::interactable() const {
    return false;
}

Button::Button(int width, int height, Vector2 position, bool interactable, Text *text,
               ButtonRenderShape buttonRenderShape) : _buttonRenderShape(std::move(buttonRenderShape)) {
    _width = width;
    _height = height;
    _position = position;
    _interactable = interactable;
    _text = std::unique_ptr<Text>{text};
    setShape();
}

RenderShape& Button::getRenderShape() {
    return _buttonRenderShape;
}


void Button::setShape() {
    // setup container of button
    auto* renderShape  = new RectRenderShape(Rect2(_position, Vector2(_width, _height)),
                                             0,
                                             Vector2(0, 0),
                                             Color(255,255,255,255));


    // setup text position relative to the container
    _text->_renderShape.setPosition(Vector2(renderShape->rect().position.x - _text->_renderShape.fontSize() * 2,
                                             renderShape->rect().position.y - _text->_renderShape.fontSize() * 0.5));

    // setup render shape
    auto* renderButton = new ButtonRenderShape(renderShape, &_text->_renderShape);
    _buttonRenderShape = *new ButtonRenderShape(renderButton->_rectRenderShape.get(),
                                                             renderButton->_textRenderShape.get());
}

void Button::onClick() {

}


