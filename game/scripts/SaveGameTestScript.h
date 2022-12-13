//
// Created by marcello on 12/13/22.
//

#ifndef GOLFENGINE_SAVEGAMETESTSCRIPT_H
#define GOLFENGINE_SAVEGAMETESTSCRIPT_H

#include <Scene/Components/BehaviourScript.h>
#include <Scene/GameObjects/GameObject.h>

class SaveGameTestScript : public BehaviourScript{
public:
    explicit SaveGameTestScript(RigidBody* playerGameObject) : _player{playerGameObject} {}
    void onUpdate() override;

private:
    RigidBody* _player;
};


#endif //GOLFENGINE_SAVEGAMETESTSCRIPT_H
