//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_MUSICVOLUMEBUTTONSCRIPT_H
#define GOLFENGINE_MUSICVOLUMEBUTTONSCRIPT_H


#include "Scene/Components/BehaviourScript.h"
#include "TextUpdateScript.h"

class MusicVolumeButtonScript : public BehaviourScript{
public:
    explicit MusicVolumeButtonScript(TextUpdateScript* script) : _textUpdateScript{script} {}
    void onUpdate() override;
private:
    TextUpdateScript* _textUpdateScript {};
};




#endif //GOLFENGINE_MUSICVOLUMEBUTTONSCRIPT_H
