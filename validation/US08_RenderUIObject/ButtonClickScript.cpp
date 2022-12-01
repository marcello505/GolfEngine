//
// Created by Lucas on 23-11-2022.
//

#include <iostream>
#include "ButtonClickScript.h"
#include "Input/ActionMap.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include <utility>

void ButtonClickScript::onUpdate() {

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();
    std::pair<int, int> buttonXRange(btn._position.x,btn._position.x + btn._width );
    std::pair<int, int> buttonYRange(btn._position.y,btn._position.y + btn._height );

    if( ActionMap::getActionMap()->isJustPressed("ClickButton")) { // if ClickButton action is just pressed,
                                                                         // which is bound to left click

        auto mousePos = ActionMap::getActionMap()->getMousePosition(); // get mouse pos
        mousePos.x += buttonXRange.first; // line up mouse range with button range
        mousePos.y += buttonYRange.first;

        if( mousePos.x >= buttonXRange.first && mousePos.x <= buttonXRange.second &&
            mousePos.y >= buttonYRange.first &&mousePos.y <= buttonYRange.second){ // if mousepos is in buttonarea
            btn.onClick(); //activate button on click
        }
    }
}


