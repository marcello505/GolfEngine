//
// Created by Lucas on 2-11-2022.
//

#include "Button.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Input/ActionMap.h"

#include <utility>
#include <Scene/GameObjects/UIObject/Alignment.h>


Button::Button(int width, int height, Vector2 position, bool interactable, std::string onClickActionName,
               Vector2 textPosition,  float textRotation, std::string textValue, size_t textFontSize, Color textColor,
               std::string textFilePath, Alignment textAlignment) {
    _width = width;
    _height = height;
    _position = position;
    _interactable = interactable;
    _text.position = textPosition;
    _text.value = std::move(textValue);
    _text.rotation = textRotation;
    _text.fontSize = textFontSize;
    _text.color = textColor;
    _text.filePath = std::move(textFilePath);
    _text.alignment = textAlignment;
    _onClickActionName = std::move(onClickActionName);
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
    auto* rectRenderShape  = new RectRenderShape(Rect2(_position, Vector2(_width, _height)),
                                             0,
                                             Vector2(0, 0),
                                             Color(255,255,255,255));

    auto* textRenderShape  = new TextRenderShape(_text.position, _text.rotation, _text.value,
                                                 _text.fontSize,_text.color, _text.filePath);

    // setup render shape
    _buttonRenderShape = std::make_unique<ButtonRenderShape>(rectRenderShape, textRenderShape,
                                                             _text.alignment);
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
        if( ActionMap::getActionMap()->isJustPressed(_onClickActionName)) { // if ClickButton action is just pressed,
            // which is bound to left-click
            onClick();
        }
    }

    GameObject::onUpdate();
}


bool Button::isClicked() {
    return _isClicked;
}




