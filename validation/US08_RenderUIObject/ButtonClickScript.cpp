//
// Created by olafv on 12/12/2022.
//

#include "ButtonClickScript.h"
#include "Scene/GameObjects/UIObject/Button.h"

void ButtonClickScript::onUpdate() {

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        btn._text.value = "Clicked!";
    }
}

