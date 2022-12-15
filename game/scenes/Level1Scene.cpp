//
// Created by Lucas on 15-12-2022.
//

#include "Level1Scene.h"
#include "Scene/Components/TiledComponent.h"
#include "../gameobjects/ProjectilePoolObject.h"
#include "../gameobjects/PlayerObject.h"
#include "Scene/GameObjects/Camera.h"

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
        auto& projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 30);
        projectilePool.setLocalPosition(Vector2{-40, -40});
        GameObject& player = scene.createNewGameObject<PlayerObject>(root, &projectilePool.getComponent<ProjectilePoolScript>());
        player.setLocalPosition(Vector2{1615, 1058});

        auto& cam = scene.createNewGameObject<Camera>(player, 1280.0f, 720.0f);
        //TODO remove the following manual offset
        cam.setLocalPosition({-640, -300});
    }

}
