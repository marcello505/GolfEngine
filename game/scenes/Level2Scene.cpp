//
// Created by marcello on 12/15/22.
//

#include "Level2Scene.h"
#include "Scene/Components/TiledComponent.h"
#include "../gameobjects/ProjectilePoolObject.h"
#include "../gameobjects/PlayerObject.h"
#include "Scene/GameObjects/Camera.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "../gameobjects/GameManager.h"
#include "../gameobjects/HUD.h"
#include "../gameobjects/EnemyObject.h"
#include "../gameobjects/FinishLevelAreaObject.h"
#include "../gameobjects/PhysicGameObject.h"

void Level2Scene::build(Scene& scene) const {
    auto& root = scene.createNewGameObject<GameObject>();
    auto& entities = scene.createNewGameObject<GameObject>(root);

    //load in tileset
    {
        auto& mapObject = scene.createNewGameObject<GameObject>(root);
        auto& mapComponent = mapObject.addComponent<TiledComponent>("res/tilesets/Level2.tmx", Vector2{3, 3});
        mapComponent.initColliders();
        mapComponent.layer=-1;

    }

    //Set up player
    auto& projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 30);
    projectilePool.setLocalPosition(Vector2{-40, -40});
    GameObject& player = scene.createNewGameObject<PlayerObject>(entities, &projectilePool.getComponent<ProjectilePoolScript>(), std::ref(scene));
    player.setLocalPosition(Vector2{3070, 1900});
    auto& cam = scene.createNewGameObject<Camera>(player);

    //PhysicsObjects
    {
        scene.createNewGameObject<PhysicGameObject>("res/sprites/kast.png", Vector2{1,1}, Vector2{24, 52}).setLocalPosition({1515, 1297});
    }

    //Enemies
    {
        //Office zombies
        {
            auto& zom1 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            zom1.setLocalPosition(Vector2{2082, 1511});
            zom1.addPatrolPoint({2161, 1510});
            zom1.addPatrolPoint({2017, 1512});
            auto& zom2 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            zom2.setLocalRotation(180);
            zom2.setLocalPosition(Vector2{2616, 886});
            zom2.addPatrolPoint(Vector2{2616, 886});
            zom2.addPatrolPoint(Vector2{1576, 893});
            auto& zom3 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            zom3.setLocalPosition(Vector2{2835, 1600});
            zom3.addPatrolPoint({2835, 1600});
            zom3.addPatrolPoint({2932, 1676});

        }

        //Monster closet zombies
        {
            auto& clos1 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            clos1.setLocalPosition(Vector2{1000, 1071});
            clos1.setLocalRotation(35);
            auto& clos2 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            clos2.setLocalPosition(Vector2{1134, 1071});
            clos2.setLocalRotation(194);
            auto& clos3 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            clos3.setLocalPosition(Vector2{1281, 1071});
            clos3.setLocalRotation(231);
            auto& clos4 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            clos4.setLocalPosition(Vector2{1000, 1305});
            clos4.setLocalRotation(123);
            auto& clos5 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            clos5.setLocalPosition(Vector2{1000, 1540});
            clos5.setLocalRotation(23);
            auto& clos6 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            clos6.setLocalPosition(Vector2{1134, 1540});
            clos6.setLocalRotation(273);
            auto& clos7 = scene.createNewGameObject<EnemyObject>(entities, &player, std::ref(scene));
            clos7.setLocalPosition(Vector2{1281, 1540});
            clos7.setLocalRotation(2);
        }
    }

    //LevelExit
    {
        scene.createNewGameObject<FinishLevelAreaObject>(entities, Vector2{2064, 624}, Vector2{96, 96});
    }

    //GameManager
    scene.createNewGameObject<GameManager>("mainMenu");

    //Set up Graph
    if(GolfEngine::Services::Pathfinding::hasService()) {
        GolfEngine::Services::Pathfinding::getService()->setGraphStartPoint(950, 425);
        GolfEngine::Services::Pathfinding::getService()->setGraphSize(3200, 1950);
        GolfEngine::Services::Pathfinding::getService()->setNodeDistance(50);
        GolfEngine::Services::Pathfinding::getService()->setMarginAroundRectColliders(10);
    }


    // IMPORTANT! Create this object after the GameManager (GameManager.onStart() needs to happen before HUD.onStart())
    scene.createNewGameObject<HUD>(std::ref(scene));
}
