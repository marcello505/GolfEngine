//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_MUSICVOLUMEBUTTONSCRIPT_H
#define GOLFENGINE_MUSICVOLUMEBUTTONSCRIPT_H


#include "Scene/Components/BehaviourScript.h"
#include "VolumeTextUpdateScript.h"

class MusicVolumeButtonScript : public BehaviourScript{
public:
    explicit MusicVolumeButtonScript(VolumeTextUpdateScript* script) : _textUpdateScript{script} {}
    void onUpdate() override;
private:
    VolumeTextUpdateScript* _textUpdateScript {};
};




#endif //GOLFENGINE_MUSICVOLUMEBUTTONSCRIPT_H
