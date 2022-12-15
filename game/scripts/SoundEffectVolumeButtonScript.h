//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_SOUNDEFFECTVOLUMEBUTTONSCRIPT_H
#define GOLFENGINE_SOUNDEFFECTVOLUMEBUTTONSCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include "VolumeTextUpdateScript.h"

class SoundEffectVolumeButtonScript : public BehaviourScript{
public:
    explicit SoundEffectVolumeButtonScript(VolumeTextUpdateScript* script) : _textUpdateScript{script} {}
    void onUpdate() override;
private:
    VolumeTextUpdateScript* _textUpdateScript {};
};


#endif //GOLFENGINE_SOUNDEFFECTVOLUMEBUTTONSCRIPT_H
