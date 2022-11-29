//
// Created by marcello on 11/29/22.
//

#include <iostream>
#include "PlayerMovementScript.h"

void PlayerMovementScript::onStart() {
    _rb = &_gameObject.value().get().getComponent<RigidBody>();
    _actionMap = ActionMap::getActionMap();
    _gunShotAudio = &_gameObject.value().get().getComponent<GolfEngine::Scene::Components::AudioSource>();
}

void PlayerMovementScript::onUpdate() {

    //Player movement logic
    {
        Vector2 inputDirection {};
        if(_actionMap->isPressed("playerLeft")){
            inputDirection.x -= 1.0f;
        }
        if(_actionMap->isPressed("playerRight")){
            inputDirection.x += 1.0f;
        }
        if(_actionMap->isPressed("playerUp")){
            inputDirection.y -= 1.0f;
        }
        if(_actionMap->isPressed("playerDown")){
            inputDirection.y += 1.0f;
        }

        _rb->applyForceToCenter(inputDirection.normalized() * playerSpeed);
    }

    //Audio
    if(_actionMap->isJustPressed("playerShoot")){
        _gunShotAudio->play();
    }
}
