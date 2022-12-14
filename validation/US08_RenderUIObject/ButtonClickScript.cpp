//
// Created by olafv on 12/12/2022.
//

#include <iostream>
#include "ButtonClickScript.h"
#include "Input/ActionMap.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include <utility>

void ButtonClickScript::onUpdate() {

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        btn._text->_renderShape.setText("Clicked!");
    }
}

