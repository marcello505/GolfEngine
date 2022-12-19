//
// Created by olafv on 12/14/2022.
//

#ifndef GOLFENGINE_BACKBUTTONSCRIPT_H
#define GOLFENGINE_BACKBUTTONSCRIPT_H


#include "Scene/Components/BehaviourScript.h"

using namespace GolfEngine::Scene::Components;

class BackButtonScript : public BehaviourScript{
public:
    void onUpdate() override;
};


#endif //GOLFENGINE_BACKBUTTONSCRIPT_H
