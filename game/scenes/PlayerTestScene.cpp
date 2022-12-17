//
// Created by marcello on 11/29/22.
//

#include "PlayerTestScene.h"
#include "Scene/Components/RigidBody.h"
#include "../gameobjects/PlayerObject.h"
#include "../gameobjects/Wall.h"
#include "../gameobjects/ProjectilePoolObject.h"
#include "../gameobjects/EnemyObject.h"
#include "Scene/Components/Animator.h"
#include "../scripts/SaveStateScript.h"
#include "../gameobjects/TestBlock.h"
#include "../scripts/MenuScripts/BackButtonScript.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/BoxCollider.h"
#include "../gameobjects/GameManager.h"
#include "Scene/GameObjects/Camera.h"
#include "../gameobjects/HUD.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "../gameobjects/FinishLevelAreaObject.h"

void PlayerTestScene::build(Scene& scene) const {

    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();
    root.addComponent<SaveStateScript>();

    //Walls
    {
        //Borders
        scene.createNewGameObject<Wall>(Vector2{640.f, 12.5f}, Vector2{640.f, 12.5f});
        scene.createNewGameObject<Wall>(Vector2{640.f, 707.5f}, Vector2{640.f, 12.5f});
        scene.createNewGameObject<Wall>(Vector2{12.5f, 360.0f}, Vector2{12.5, 360.0f});
        scene.createNewGameObject<Wall>(Vector2{1267.5f, 360.0f}, Vector2{12.5, 360.0f});

        //Inside borders
        scene.createNewGameObject<Wall>(Vector2{640.0f, 360.0f}, Vector2{12.5, 125.0f});
    }

    //Objects
    {
        scene.createNewGameObject<TestBlock>(Vector2{200.0f, 500.0f});
        scene.createNewGameObject<TestBlock>(Vector2{100.0f, 250.0f});
        scene.createNewGameObject<TestBlock>(Vector2{312.0f, 346.0f});

    }

    auto& projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 20);

    auto& player = scene.createNewGameObject<PlayerObject>(&projectilePool.getComponent<ProjectilePoolScript>());
    player.setLocalPosition({200.f, 200.f});
    // Add camera to player
    scene.createNewGameObject<Camera>((GameObject&)player);

    //Finish area
    scene.createNewGameObject<FinishLevelAreaObject>(Vector2{1000.0f, 100.0f}, Vector2{50.0f, 50.0f});

    auto& testEnemyCollision = scene.createNewGameObject<GameObject>();
    testEnemyCollision.addComponent<BoxCollider>(Vector2{25.0f, 25.0f});
    testEnemyCollision.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
    testEnemyCollision.tag = "enemy";
    testEnemyCollision.setLocalPosition({1000.0f, 500.0f});

 auto& enemy1 = scene.createNewGameObject<EnemyObject>(root, &player);
    enemy1.setLocalPosition({700.f, 400.f});
    enemy1.originalTransform = Transform({700.f, 400.f}, 0, {1,1});
    enemy1.addPatrolPoint({700.f, 400.f});
    enemy1.addPatrolPoint({800,400});
    enemy1.addPatrolPoint({800,500});
    enemy1.addPatrolPoint({700,500});

    auto& enemy2 = scene.createNewGameObject<EnemyObject>(root, &player);
    enemy2.setLocalPosition({800.f, 100.f});
    enemy2.addPatrolPoint({800.f, 400.f});
    enemy2.addPatrolPoint({700.f, 50.f});
    enemy2.addPatrolPoint({700.f, 400.f});

    auto& enemy3 = scene.createNewGameObject<EnemyObject>(root, &player);
   enemy3.setLocalPosition({400.f, 150.f});
   auto& enemy4 = scene.createNewGameObject<EnemyObject>(root, &player);
   enemy4.setLocalPosition({850.f, 150.f});

    scene.createNewGameObject<GameManager>("mainMenu");

    GolfEngine::Services::Pathfinding::getService()->setGraphSize(1280, 720);
    GolfEngine::Services::Pathfinding::getService()->setNodeDistance(50);

    // IMPORTANT! Create this object after the GameManager (GameManager.onStart() needs to happen before HUD.onStart())
    scene.createNewGameObject<HUD>(std::ref(scene));
}
