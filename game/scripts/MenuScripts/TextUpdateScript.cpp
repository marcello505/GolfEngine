//
// Created by olafv on 12/12/2022.
//

#include <sstream>
#include <utility>
#include "Core/GameLoop.h"
#include "TextUpdateScript.h"
#include "Scene/GameObjects/UIObject/Button.h"

void TextUpdateScript::SetNewText(std::string newText){
    //update text
    _newText = std::move(newText);
    _text->_renderShape.setText(_newText);
}

