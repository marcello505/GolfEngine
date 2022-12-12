//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Input/ActionMap.h"

#include <utility>
#include <Scene/GameObjects/UIObject/Alignment.h>


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
    _isClicked = true;
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

void Button::onUpdate() {

    _isClicked = false;

    if( ActionMap::getActionMap()->isJustPressed("ClickButton")) { // if ClickButton action is just pressed,
        // which is bound to left-click

        //get range of button area to check if we clicked there
        std::pair<int, int> buttonXRange(_position.x,_position.x + _width );
        std::pair<int, int> buttonYRange(_position.y,_position.y + _height );

        auto mousePos = ActionMap::getActionMap()->getMousePosition(); // get mouse pos
        mousePos.x += 50; // surplus mouserange with visual range
        mousePos.y += 30;

        if( mousePos.x >= buttonXRange.first && mousePos.x <= buttonXRange.second &&
            mousePos.y >= buttonYRange.first &&mousePos.y <= buttonYRange.second){ // if mousepos is in buttonarea
            onClick();
        }
    }

    GameObject::onUpdate();
}

bool Button::isClicked() {
    return _isClicked;
}




