//
// Created by olafv on 12/14/2022.
//

#ifndef GOLFENGINE_MASTERVOLUMEBUTTONSCRIPT_H
#define GOLFENGINE_MASTERVOLUMEBUTTONSCRIPT_H


#include "Scene/Components/BehaviourScript.h"
#include "VolumeTextUpdateScript.h"

class MasterVolumeButtonScript : public BehaviourScript{
public:
    explicit MasterVolumeButtonScript(VolumeTextUpdateScript* script) : _textUpdateScript{script} {}
    void onUpdate() override;
private:
    VolumeTextUpdateScript* _textUpdateScript {};
};


#endif //GOLFENGINE_MASTERVOLUMEBUTTONSCRIPT_H
