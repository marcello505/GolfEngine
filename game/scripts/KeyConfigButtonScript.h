//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_KEYCONFIGBUTTONSCRIPT_H
#define GOLFENGINE_KEYCONFIGBUTTONSCRIPT_H


#include <utility>

#include "Scene/Components/BehaviourScript.h"

class KeyConfigButtonScript : public BehaviourScript{
public:
    explicit KeyConfigButtonScript(std::string actionName) : _actionName{std::move(actionName)} {}
    void onUpdate() override;
private:
    std::string _actionName;
    bool showingKeyConfigScene = false;
};



#endif //GOLFENGINE_KEYCONFIGBUTTONSCRIPT_H
