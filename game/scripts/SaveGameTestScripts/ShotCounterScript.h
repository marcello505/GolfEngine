//
// Created by marcello on 12/14/22.
//

#ifndef GOLFENGINE_SHOTCOUNTERSCRIPT_H
#define GOLFENGINE_SHOTCOUNTERSCRIPT_H

#include "Scene/GameObjects/UIObject/Text.h"
#include "Scene/Components/BehaviourScript.h"

class ShotCounterScript : public BehaviourScript {
public:
    explicit ShotCounterScript(Text* pText) : _text{pText} {}

    int shotsFired {0};

    void onUpdate() override;
    void updateText();


private:
    Text* _text {};
};


#endif //GOLFENGINE_SHOTCOUNTERSCRIPT_H
