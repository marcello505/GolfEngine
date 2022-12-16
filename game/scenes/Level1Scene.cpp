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

void Level1Scene::build(Scene& scene) const {
    auto& root = scene.createNewGameObject<GameObject>();

    //load in tileset
    {
        auto& mapObject = scene.createNewGameObject<GameObject>(root);
        auto& mapComponent = mapObject.addComponent<TiledComponent>("res/tilesets/Level1.tmx", Vector2{3, 3});
        mapComponent.initColliders();
    }

    //Set up player
    {
        auto &projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 20);

        auto &player = scene.createNewGameObject<PlayerObject>(&projectilePool.getComponent<ProjectilePoolScript>());
        player.setLocalPosition({1400.f, 1000.f});
        // Add camera to player
        scene.createNewGameObject<Camera>((GameObject &) player);
    }
    //setup PhysicsObjects
    {
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


    }


    scene.createNewGameObject<GameManager>();


}
