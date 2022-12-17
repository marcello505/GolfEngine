//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_TEXTUPDATESCRIPT_H
#define GOLFENGINE_TEXTUPDATESCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include "Scene/GameObjects/UIObject/Text.h"
#include "Scene/ISceneFactory.h"

class TextUpdateScript : public BehaviourScript{
public:
    explicit TextUpdateScript(Text* pText) : _text{pText}, _newText{pText->_renderShape.text()}{}
    void SetNewText(std::string newText);
private:
    Text* _text {};
    std::string _newText;
};

#endif //GOLFENGINE_TEXTUPDATESCRIPT_H
