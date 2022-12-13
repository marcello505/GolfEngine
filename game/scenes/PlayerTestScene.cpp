//
// Created by marcello on 11/29/22.
//

#include "PlayerTestScene.h"
#include "Scene/Components/RigidBody.h"
#include "../gameobjects/PlayerObject.h"
#include "../gameobjects/Wall.h"
#include "../gameobjects/Projectile.h"
#include "../gameobjects/ProjectilePoolObject.h"
#include "../gameobjects/EnemyObject.h"
#include "Scene/Components/Animator.h"
#include "../scripts/SaveStateScript.h"
#include "../gameobjects/TestBlock.h"

void PlayerTestScene::build(Scene& scene) const {
    auto& root = scene.createNewGameObject<GameObject>();
    root.addComponent<SaveStateScript>();

    //Walls
    {
        //Borders
        scene.createNewGameObject<Wall>(root, Vector2{640.f, 12.5f}, Vector2{640.f, 12.5f});
        scene.createNewGameObject<Wall>(root, Vector2{640.f, 707.5f}, Vector2{640.f, 12.5f});
        scene.createNewGameObject<Wall>(root, Vector2{12.5f, 360.0f}, Vector2{12.5, 360.0f});
        scene.createNewGameObject<Wall>(root, Vector2{1267.5f, 360.0f}, Vector2{12.5, 360.0f});

        //Inside borders
        scene.createNewGameObject<Wall>(root, Vector2{640.0f, 340.0f}, Vector2{12.5, 300.0f});
    }

    //Objects
    {
        scene.createNewGameObject<TestBlock>(root, Vector2{200.0f, 500.0f});
        scene.createNewGameObject<TestBlock>(root, Vector2{100.0f, 250.0f});
        scene.createNewGameObject<TestBlock>(root, Vector2{312.0f, 346.0f});

    }

    auto& projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 20);

    GameObject& player = scene.createNewGameObject<PlayerObject>(root, &projectilePool.getComponent<ProjectilePoolScript>());
    player.setLocalPosition({200.f, 200.f});



    auto& enemy = scene.createNewGameObject<EnemyObject>(root, &player);
    enemy.setLocalPosition({400.f, 400.f});
    auto& enemy1 = scene.createNewGameObject<EnemyObject>(root, &player);
    enemy1.setLocalPosition({750.f, 400.f});
    auto& enemy2 = scene.createNewGameObject<EnemyObject>(root, &player);
    enemy2.setLocalPosition({800.f, 100.f});
    auto& enemy3 = scene.createNewGameObject<EnemyObject>(root, &player);
    enemy3.setLocalPosition({400.f, 150.f});




}
