//
// Created by conner on 12/13/2022.
//

#ifndef GOLFENGINE_PLAYERCOLLISIONSCRIPT_H
#define GOLFENGINE_PLAYERCOLLISIONSCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include "GameManagerScript.h"
#include "PlayerMovementScript.h"

class PlayerCollisionScript : public BehaviourScript {
    void onStart() override;
    void onCollisionEnter(RigidBody& other) override;
    void onAreaEnter(RigidBody& other) override;
private:
    GameManagerScript* _gameManager;
    PlayerMovementScript* _playerMovement;
};


#endif //GOLFENGINE_PLAYERCOLLISIONSCRIPT_H
