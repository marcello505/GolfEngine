//
// Created by olafv on 12/14/2022.
//

#ifndef GOLFENGINE_SETTINGSBUTTONSCRIPT_H
#define GOLFENGINE_SETTINGSBUTTONSCRIPT_H


#include "Scene/Components/BehaviourScript.h"

using namespace GolfEngine::Scene::Components;

class SettingsButtonScript : public BehaviourScript{
public:
    virtual void onUpdate() override;
};

#endif //GOLFENGINE_SETTINGSBUTTONSCRIPT_H
