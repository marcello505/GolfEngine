//
// Created by olafv on 12/17/2022.
//

#include "Level3Scene.h"
#include "Scene/Components/TiledComponent.h"
#include "../gameobjects/ProjectilePoolObject.h"
#include "../gameobjects/PlayerObject.h"
#include "Scene/GameObjects/Camera.h"
#include "../gameobjects/GameManager.h"
#include "../gameobjects/PhysicGameObject.h"
#include "../gameobjects/EnemyObject.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "../gameobjects/HUD.h"
#include "../gameobjects/FinishLevelAreaObject.h"

void Level3Scene::build(Scene& scene) const {
    auto& root = scene.createNewGameObject<GameObject>();
    auto& levelMusic = root.addComponent<GolfEngine::Scene::Components::AudioSource>(true, true, true);
    levelMusic.addSound("level3", "res/music/long_night.mp3");
    levelMusic.volume = 0.3f;

    //load in tileset
    {
        auto& mapObject = scene.createNewGameObject<GameObject>(root);
        auto& mapComponent = mapObject.addComponent<TiledComponent>("res/tilesets/Level3.tmx", Vector2{3, 3});
        mapComponent.initColliders();
        mapComponent.layer = -1;
    }

    //Set up player
    auto &projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 20);

    auto &player = scene.createNewGameObject<PlayerObject>(&projectilePool.getComponent<ProjectilePoolScript>(), std::ref(scene));
    player.setLocalPosition({2080.f, 830.f});
    // Add camera to players
    scene.createNewGameObject<Camera>((GameObject &) player);

    //setup physics
    auto& crate1 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
    crate1.setLocalPosition({2160,1100});
    auto& crate2 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
    crate2.setLocalPosition({2160,1150});
    auto& crate3 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
    crate3.setLocalPosition({2160,1200});

    auto& crate4 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
    crate4.setLocalPosition({1130,1620});
    auto& crate5 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
    crate5.setLocalPosition({1130,1671});
    auto& crate6 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
    crate6.setLocalPosition({1130,1722});


    //Setup enemies
    {
        auto& enemy1 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy1.setLocalPosition({2630.f, 1240.f});
        enemy1.addPatrolPoint({2330.f, 1240.f});
        enemy1.addPatrolPoint({2530.f, 1140.f});
        enemy1.addPatrolPoint({2630.f, 1240.f});

        auto& enemy2 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy2.setLocalPosition({2320.f, 1150.f});

        auto& enemy3 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy3.setLocalPosition({1715.f, 1866.f});

        auto& enemy4 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy4.setLocalPosition({1060.f, 1520.f});

        auto& enemy5 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy5.setLocalPosition({1440.f, 890.f});
        enemy5.addPatrolPoint({850.f, 750.f});
        enemy5.addPatrolPoint({720.f, 930.f});
        enemy5.addPatrolPoint({1000.f, 750.f});

        auto& enemy6 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy6.setLocalPosition({1000.f, 750.f});


        auto& enemy7 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy7.setLocalPosition({1540.f, 770.f});


        auto& enemy8 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy8.setLocalPosition({1670.f, 350.f});
        enemy8.addPatrolPoint({1370.f, 350.f});
        enemy8.addPatrolPoint({1370.f, 550.f});
        enemy8.addPatrolPoint({1670.f, 350.f});
    }

    //Finish area
    scene.createNewGameObject<FinishLevelAreaObject>(Vector2{1300.0f, 400.0f}, Vector2{50.0f, 50.0f});

    scene.createNewGameObject<GameManager>("youWonScene");

    if(GolfEngine::Services::Pathfinding::hasService()) {
        GolfEngine::Services::Pathfinding::getService()->setGraphStartPoint(0, 0);
        GolfEngine::Services::Pathfinding::getService()->setGraphSize(2850, 2100);
        GolfEngine::Services::Pathfinding::getService()->setNodeDistance(50);
        GolfEngine::Services::Pathfinding::getService()->setMarginAroundRectColliders(0);
    }

    // IMPORTANT! Create this object after the GameManager (GameManager.onStart() needs to happen before HUD.onStart())
    scene.createNewGameObject<HUD>(std::ref(scene));

}