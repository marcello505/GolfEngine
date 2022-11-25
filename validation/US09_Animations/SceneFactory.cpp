//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/Animator.h"
#include "ZombieScript.h"

void SceneFactory::build(Scene& scene) const {
    auto& player = scene.createNewGameObject<GameObject>();
    player.addComponent<SpriteComponent>(R"(..\..\..\validation\US09_Animations\res\player.png)");
    player.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(0.5f,0.5f)));

    auto& enemy = scene.createNewGameObject<GameObject>();
    enemy.addComponent<ZombieScript>();
    auto& animator = enemy.addComponent<Animator>(R"(..\..\..\validation\US09_Animations\res\zombie_spritesheet.png)", 7, 7, Vector2(239, 221));
    animator.addAnimation("attack", 0, 8, 15.0f);
    animator.addAnimation("idle", 9, 25, 15.0f);
    animator.addAnimation("moving", 26, 42, 15.0f);
    animator.addReturnTransition("attack", "idle");
    animator.play("idle", true);
    enemy.setWorldTransform(Transform(Vector2(400, 200), 0, Vector2(0.1f, 0.1f)));
}