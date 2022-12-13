//
// Created by marcello on 11/29/22.
//

#include "PlayerObject.h"

#include <Scene/Components/BoxCollider.h>
#include <Scene/Components/AudioSource.h>
#include <Scene/Components/SpriteComponent.h>

#include "../scripts/PlayerMovementScript.h"
#include "../scripts/PlayerShootScript.h"
#include "../scripts/GameManagerScript.h"
#include "../scripts/PlayerCollisionScript.h"


PlayerObject::PlayerObject(ProjectilePoolScript* projectilePoolScript) {
    addComponent<BoxCollider>(Vector2{25.f, 25.f});

    RigidBodyDef rbDef {};

    rbDef.fixedRotation = true;
    rbDef.linearDamping = 5.0f;

    addComponent<SpriteComponent>("res/sprite_sheets/out.png", Vector2{1.0f, 1.0f}, Rect2{}, Vector2{}, 0, Vector2{40, 70});
    auto& animator = addComponent<Animator>("res/sprite_sheets/out.png", 6, 8, Vector2{128.0f, 126.0f});
    animator.addAnimation("idle", 0, 19, 15.0f);
    //animator.addAnimation("walk", 20, 39, 15.0f);
    animator.addAnimation("shoot", 40, 42, 25.0f);
    animator.addReturnTransition("shoot", "idle");

    addComponent<RigidBody>(rbDef);
    addComponent<PlayerMovementScript>();
    addComponent<PlayerShootScript>(projectilePoolScript, 10);
    addComponent<GolfEngine::Scene::Components::AudioSource>("res/audio/short-shot.ogg", false);
    addComponent<PlayerCollisionScript>();
    addComponent<GameManagerScript>();
}
