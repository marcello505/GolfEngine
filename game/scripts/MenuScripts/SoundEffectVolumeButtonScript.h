//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_SOUNDEFFECTVOLUMEBUTTONSCRIPT_H
#define GOLFENGINE_SOUNDEFFECTVOLUMEBUTTONSCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include "TextUpdateScript.h"

using namespace GolfEngine::Scene::Components;

class SoundEffectVolumeButtonScript : public BehaviourScript{
public:
    explicit SoundEffectVolumeButtonScript(TextUpdateScript* script) : _textUpdateScript{script} {}
    void onUpdate() override;
private:
    TextUpdateScript* _textUpdateScript {};
};


#endif //GOLFENGINE_SOUNDEFFECTVOLUMEBUTTONSCRIPT_H
