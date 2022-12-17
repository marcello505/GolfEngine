//
// Created by conner on 12/13/2022.
//

#ifndef GOLFENGINE_GAMEMANAGERSCRIPT_H
#define GOLFENGINE_GAMEMANAGERSCRIPT_H

#include "Scene/Components/BehaviourScript.h"

class GameManagerScript : public BehaviourScript {
public:
    void restartLevel();
    void tryFinishLevel();
private:
    void onStart() override;
    void onUpdate() override;
    void finishLevel();

};


#endif //GOLFENGINE_GAMEMANAGERSCRIPT_H
