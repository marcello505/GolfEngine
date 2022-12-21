//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/Animator.h"
#include "ZombieScript.h"
#include "Scene/Components/BehaviourScript.h"
#include "Input/ActionMap.h"

using namespace GolfEngine::Scene;
using namespace GolfEngine::Input;

class TestScript : public BehaviourScript {
    void onUpdate() override{
        if(ActionMap::getActionMap()->isJustPressed("test"))
            _gameObject->get().setActive(!_gameObject->get().getActive());
    }
};

void SceneFactory::build(Scene& scene) const {
    auto& player = scene.createNewGameObject<GameObject>();
    player.addComponent<SpriteComponent>(R"(../../../validation/US09_Animations/res/player.png)");
    player.addComponent<TestScript>();
    player.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(1,1)));


    auto& enemy = scene.createNewGameObject<GameObject>();
    enemy.addComponent<ZombieScript>();
    auto& animator = enemy.addComponent<Animator>(R"(../../../validation/US09_Animations/res/zombie_spritesheet.png)", 7, 7, Vector2(239, 221));
    animator.addAnimation("attack", 0, 8, 15.0f);
    animator.addAnimation("idle", 9, 25, 15.0f);
    animator.addAnimation("moving", 26, 42, 15.0f);
    animator.addReturnTransition("attack", "idle");
    animator.play("moving", true);
    enemy.setWorldTransform(Transform(Vector2(400, 200), 0, Vector2(0.1f, 0.1f)));
    animator.play("idle", true);
    enemy.setWorldTransform(Transform(Vector2(400, 200), 0, Vector2(1.0f, 1.0f)));
}