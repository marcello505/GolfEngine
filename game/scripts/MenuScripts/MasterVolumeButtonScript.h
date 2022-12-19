//
// Created by olafv on 12/14/2022.
//

#ifndef GOLFENGINE_MASTERVOLUMEBUTTONSCRIPT_H
#define GOLFENGINE_MASTERVOLUMEBUTTONSCRIPT_H


#include "Scene/Components/BehaviourScript.h"
#include "TextUpdateScript.h"

using namespace GolfEngine::Scene::Components;

class MasterVolumeButtonScript : public BehaviourScript{
public:
    explicit MasterVolumeButtonScript(TextUpdateScript* script) : _textUpdateScript{script} {}
    void onUpdate() override;
private:
    TextUpdateScript* _textUpdateScript {};
};


#endif //GOLFENGINE_MASTERVOLUMEBUTTONSCRIPT_H
