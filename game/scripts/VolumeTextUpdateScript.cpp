//
// Created by olafv on 12/12/2022.
//

#include <sstream>
#include <utility>
#include "Core/GameLoop.h"
#include "VolumeTextUpdateScript.h"
#include "Scene/GameObjects/UIObject/Button.h"

void VolumeTextUpdateScript::SetNewText(std::string newText){
    _newText = std::move(newText);
    _text->_renderShape.setText(_newText);
}


