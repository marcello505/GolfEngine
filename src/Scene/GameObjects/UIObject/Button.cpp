//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Input/ActionMap.h"

#include <utility>
#include <Scene/GameObjects/UIObject/Alignment.h>
#include <iostream>
#include <SDL_surface.h>
#include <SDL_ttf.h>


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

    // setup render shape
    _buttonRenderShape = std::make_unique<ButtonRenderShape>(renderShape, &_text->_renderShape,
                                                             *&_text->_alignment);
    GolfEngine::Services::Render::getService()->addDrawable(*this);
}


bool Button::interactable() const {
    return _interactable;
}




