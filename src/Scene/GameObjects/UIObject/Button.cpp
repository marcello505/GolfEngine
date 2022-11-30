//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Input/ActionMap.h"

#include <utility>
#include <Scene/GameObjects/UIObject/Alignment.h>
#include <iostream>



Button::Button(int width, int height, Vector2 position, bool interactable, Text *text) {
    _width = width;
    _height = height;
    _position = position;
    _interactable = interactable;
    _text = std::unique_ptr<Text>{text};
    setShape();
}

RenderShape& Button::getRenderShape() {
    return *_buttonRenderShape;
}

void Button::onClick() {
     _buttonRenderShape->_textRenderShape->setText("Clicked!");
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
    _buttonRenderShape = std::make_unique<ButtonRenderShape>(renderShape, &_text->_renderShape);
}


bool Button::interactable() const {
    return _interactable;
}




