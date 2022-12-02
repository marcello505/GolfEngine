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


PlayerObject::PlayerObject(ProjectilePoolScript* projectilePoolScript, bool useAnimator) {
    addComponent<BoxCollider>(Vector2{12.5f, 12.5f});

    RigidBodyDef rbDef {};

    rbDef.fixedRotation = true;
    rbDef.linearDamping = 5.0f;

    if(useAnimator){
        addComponent<SpriteComponent>("res/sprite_sheets/out_nums.png", Vector2{7.0f, 7.0f});
        auto& animator = addComponent<Animator>("res/sprite_sheets/out_nums.png", 6, 8, Vector2{128.0f, 126.0f});
        animator.addAnimation("idle", 0, 19, 1.0f);
        animator.addAnimation("walk", 20, 39, 1.0f);
        animator.addAnimation("shoot", 40, 42, 1.0f);
        animator.addReturnTransition("shoot", "idle");
    }
    else{
        addComponent<SpriteComponent>("res/sprites/player.png", Vector2{5.0f, 5.0f});
    }

    addComponent<RigidBody>(rbDef);
    addComponent<PlayerMovementScript>(projectilePoolScript);
    addComponent<GolfEngine::Scene::Components::AudioSource>("res/audio/short-shot.ogg", false);

}
