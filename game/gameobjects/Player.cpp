//
// Created by marcello on 11/29/22.
//

#include "Player.h"

#include <Scene/Components/RigidBody.h>
#include <Scene/Components/BoxCollider.h>
#include <Scene/Components/AudioSource.h>
#include <Scene/Components/SpriteComponent.h>

#include "../scripts/PlayerMovementScript.h"


Player::Player() {
    addComponent<BoxCollider>(Vector2{12.5f, 12.5f});

    RigidBodyDef rbDef {};

    rbDef.fixedRotation = true;
    rbDef.linearDamping = 5.0f;

    addComponent<RigidBody>(rbDef);
    addComponent<PlayerMovementScript>();
    addComponent<GolfEngine::Scene::Components::AudioSource>("res/audio/short-shot.ogg", false);
    addComponent<SpriteComponent>("res/sprites/player.png", Vector2{5.0f, 5.0f});
}
