//
// Created by marcello on 11/29/22.
//

#include "PlayerObject.h"

#include <Scene/Components/RigidBody.h>
#include <Scene/Components/BoxCollider.h>
#include <Scene/Components/AudioSource.h>
#include <Scene/Components/SpriteComponent.h>

#include "../scripts/PlayerMovementScript.h"
#include "Scene/Components/Animator.h"


PlayerObject::PlayerObject(ProjectilePoolScript* projectilePoolScript) {
    addComponent<BoxCollider>(Vector2{12.5f, 12.5f});

    RigidBodyDef rbDef {};

    rbDef.fixedRotation = true;
    rbDef.linearDamping = 5.0f;

    addComponent<SpriteComponent>("res/sprite_sheets/out.png", Vector2{12.0f, 12.0f});
    auto& animator = addComponent<Animator>("res/sprite_sheets/out.png", 6, 8, Vector2{128.0f, 126.0f});
    animator.addAnimation("idle", 0, 19, 15.0f);
    //animator.addAnimation("walk", 20, 39, 15.0f);
    animator.addAnimation("shoot", 40, 42, 15.0f);
    animator.addReturnTransition("shoot", "idle");

    addComponent<RigidBody>(rbDef);
    addComponent<PlayerMovementScript>(projectilePoolScript);
    addComponent<GolfEngine::Scene::Components::AudioSource>("res/audio/short-shot.ogg", false);

}
