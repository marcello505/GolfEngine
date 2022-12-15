//
// Created by marcello on 12/14/22.
//

#include <sstream>

#include <Input/ActionMap.h>

#include "ShotCounterScript.h"

void ShotCounterScript::onUpdate() {
    auto& actionMap = *ActionMap::getActionMap();

    if(actionMap.isJustPressed("playerShoot")){
        shotsFired++;
        updateText();
    }

}

void ShotCounterScript::updateText() {
    std::stringstream updatedText {};
    updatedText << "Shots Fired: " << shotsFired;
    _text->_renderShape.setText(updatedText.str());
}
