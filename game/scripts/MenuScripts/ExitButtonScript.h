//
// Created by olafv on 12/14/2022.
//

#ifndef GOLFENGINE_EXITBUTTONSCRIPT_H
#define GOLFENGINE_EXITBUTTONSCRIPT_H

#include "Scene/Components/BehaviourScript.h"

using namespace GolfEngine::Scene::Components;

class ExitButtonScript : public BehaviourScript{
public:
    void onUpdate() override;
};

#endif //GOLFENGINE_EXITBUTTONSCRIPT_H
