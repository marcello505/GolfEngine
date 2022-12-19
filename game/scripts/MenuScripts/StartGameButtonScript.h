//
// Created by olafv on 12/12/2022.
//

#ifndef GOLFENGINE_BUTTONCLICKSCRIPT_H
#define GOLFENGINE_BUTTONCLICKSCRIPT_H


#include "Scene/Components/BehaviourScript.h"

using namespace GolfEngine::Scene::Components;

class StartGameButtonScript : public BehaviourScript{
public:
    virtual void onUpdate() override;
};


#endif //GOLFENGINE_BUTTONCLICKSCRIPT_H
