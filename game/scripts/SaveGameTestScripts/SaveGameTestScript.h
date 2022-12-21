//
// Created by marcello on 12/13/22.
//

#ifndef GOLFENGINE_SAVEGAMETESTSCRIPT_H
#define GOLFENGINE_SAVEGAMETESTSCRIPT_H

#include <Scene/Components/BehaviourScript.h>
#include <Scene/GameObjects/GameObject.h>
#include "ShotCounterScript.h"

using namespace GolfEngine::Scene::Components;

class SaveGameTestScript : public BehaviourScript{
public:
    explicit SaveGameTestScript(RigidBody* playerGameObject, ShotCounterScript* shotCounterScript) : _player{playerGameObject}, _shotCounterScript{shotCounterScript} {}
    void onUpdate() override;

private:
    RigidBody* _player;
    ShotCounterScript* _shotCounterScript;
};


#endif //GOLFENGINE_SAVEGAMETESTSCRIPT_H
