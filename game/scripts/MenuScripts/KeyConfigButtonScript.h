//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_KEYCONFIGBUTTONSCRIPT_H
#define GOLFENGINE_KEYCONFIGBUTTONSCRIPT_H


#include <utility>

#include "Scene/Components/BehaviourScript.h"
#include "Scene/GameObjects/UIObject/Text.h"
#include "TextUpdateScript.h"

class KeyConfigButtonScript : public BehaviourScript{
public:
    explicit KeyConfigButtonScript(std::string actionName, TextUpdateScript* script) : _textUpdateScript{script},
    _actionName{std::move(actionName)} {}

    void onUpdate() override;
private:
    Text* _text {};
    std::string _actionName;
    TextUpdateScript* _textUpdateScript {};
};



#endif //GOLFENGINE_KEYCONFIGBUTTONSCRIPT_H
