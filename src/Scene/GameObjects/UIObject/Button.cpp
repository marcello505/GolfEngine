//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Input/ActionMap.h"

#include <utility>
#include <Scene/GameObjects/UIObject/Alignment.h>


Button::Button(int width, int height, Vector2 position, bool interactable, Text *text, std::string onClickActionName) {
    _width = width;
    _height = height;
    _position = position;
    _interactable = interactable;
    _text = text;
    _onClickActionName =onClickActionName;
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
    if(GolfEngine::Services::Render::hasService())
        GolfEngine::Services::Render::getService()->addDrawable(*this);
}

Button::~Button() {
    if(GolfEngine::Services::Render::hasService())
        GolfEngine::Services::Render::getService()->removeDrawable(*this);
}


bool Button::interactable() const {
    return _interactable;
}

void Button::onUpdate() {

    _isClicked = false;

    std::pair<int, int> buttonXRange(_position.x - (_width / 2),_position.x - (_width / 2) + _width );
    std::pair<int, int> buttonYRange(_position.y - (_height / 2),_position.y - (_height / 2) + _height );


    //get range of button area to check if we clicked there

    auto mousePos = ActionMap::getActionMap()->getMousePosition(); // get mouse pos

    if( mousePos.x >= buttonXRange.first && mousePos.x <= buttonXRange.second &&
        mousePos.y >= buttonYRange.first &&mousePos.y <= buttonYRange.second){ // if mousepos is in buttonarea

        _buttonRenderShape->_rectRenderShape->setColor(Color(255, 0, 0));

        if( ActionMap::getActionMap()->isJustPressed(_onClickActionName)) { // if ClickButton action is just pressed,
            // which is bound to left-click
            onClick();
        }
    }else{
        _buttonRenderShape->_rectRenderShape->setColor(Color(255,255,255,255 ));
    }

    GameObject::onUpdate();
}

bool Button::isClicked() {
    return _isClicked;
}




