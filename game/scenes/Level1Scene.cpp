//
// Created by Lucas on 15-12-2022.
//

#include "Level1Scene.h"
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

void Level1Scene::build(Scene& scene) const {
    auto& root = scene.createNewGameObject<GameObject>();

    //load in tileset
    {
        auto& mapObject = scene.createNewGameObject<GameObject>(root);
        auto& mapComponent = mapObject.addComponent<TiledComponent>("res/tilesets/Level1.tmx", Vector2{3, 3});
        mapComponent.initColliders();
        mapComponent.layer=-1;
    }

    //Set up player
        auto &projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 20);

        auto &player = scene.createNewGameObject<PlayerObject>(&projectilePool.getComponent<ProjectilePoolScript>(), std::ref(scene));
        player.setLocalPosition({1400.f, 1000.f});
        // Add camera to player
        scene.createNewGameObject<Camera>((GameObject &) player);

    //Finish area
    scene.createNewGameObject<FinishLevelAreaObject>(Vector2{700.0f, 290.0f}, Vector2{50.0f, 50.0f});

    //setup PhysicsObjects
        auto& crate1 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
        crate1.setLocalPosition({1100,1000});
        auto& crate2 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
        crate2.setLocalPosition({1100,940});


        auto& crate3 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
        crate3.setLocalPosition({850,440});
        auto& crate4 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
        crate4.setLocalPosition({900,500});

        auto& crate5 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
        crate5.setLocalPosition({740,710});
        auto& crate6 = scene.createNewGameObject<PhysicGameObject>("res/sprites/crate.png",Vector2{10,10});
        crate6.setLocalPosition({720,790});

    //setup enemies
        auto& enemy1 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
        enemy1.setLocalPosition({1740.f, 1750.f});
        enemy1.addPatrolPoint({1740.f, 1750.f});
        enemy1.addPatrolPoint({1740.f, 1650.f});
        enemy1.addPatrolPoint({1540.f, 1650.f});
        enemy1.addPatrolPoint({1740.f, 1650.f});

     auto& enemy2 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
     enemy2.setLocalPosition({1540.f, 1600.f});

    auto& enemy3 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy3.setLocalPosition({880.f, 1470.f});
    auto& enemy4 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy4.setLocalPosition({1100.f, 1500.f});

    auto& enemy5 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy5.setLocalPosition({1040.f, 990.f});

    auto& enemy6 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy6.setLocalPosition({330.f, 1140.f});

    auto& enemy7 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy7.setLocalPosition({640.f, 800.f});
    enemy7.addPatrolPoint({640.f, 800.f});
    enemy7.addPatrolPoint({390.f, 800.f});
    enemy7.addPatrolPoint({390.f, 1130.f});
    enemy7.addPatrolPoint({700.f, 1130.f});
    enemy7.addPatrolPoint({390.f, 1130.f});
    enemy7.addPatrolPoint({390.f, 800.f});



    auto& enemy8 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy8.setLocalPosition({880.f, 530.f});
    enemy8.addPatrolPoint({880.f, 530.f});
    enemy8.addPatrolPoint({880.f, 800.f});

    auto& enemy9 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy9.setLocalPosition({800.f, 500.f});
    enemy9.addPatrolPoint({800.f, 500.f});
    enemy9.addPatrolPoint({800.f, 1540.f});

    auto& enemy10 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy10.setLocalPosition({1000.f, 340.f});

    auto& enemy11 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy11.setLocalPosition({1060.f, 340.f});

    auto& enemy12 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy12.setLocalPosition({1000.f, 470.f});

    auto& enemy13 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy13.setLocalPosition({1050.f, 230.f});
    enemy13.addPatrolPoint({1050.f, 230.f});
    enemy13.addPatrolPoint({660.f, 230.f});

    auto& enemy14 = scene.createNewGameObject<EnemyObject>(root, &player, std::ref(scene));
    enemy14.setLocalPosition({870.f, 300.f});

    scene.createNewGameObject<GameManager>("mainMenu");

    if(GolfEngine::Services::Pathfinding::hasService()) {
        GolfEngine::Services::Pathfinding::getService()->setGraphStartPoint(0, 0);
        GolfEngine::Services::Pathfinding::getService()->setGraphSize(1980, 1980);
        GolfEngine::Services::Pathfinding::getService()->setNodeDistance(50);
    }
    // IMPORTANT! Create this object after the GameManager (GameManager.onStart() needs to happen before HUD.onStart())
    scene.createNewGameObject<HUD>(std::ref(scene));


}
