//
// Created by marcello on 11/29/22.
//

#include "PlayerTestScene.h"
#include "Scene/Components/RigidBody.h"
#include "../gameobjects/PlayerObject.h"
#include "../gameobjects/Wall.h"
#include "../gameobjects/Projectile.h"
#include "../gameobjects/ProjectilePoolObject.h"
#include "../scripts/SaveStateScript.h"

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
        scene.createNewGameObject<Wall>(root, Vector2{640.0f, 360.0f}, Vector2{12.5, 125.0f});
    }

    auto& projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 20);

    auto& player = scene.createNewGameObject<PlayerObject>(root, &projectilePool.getComponent<ProjectilePoolScript>());
    player.setLocalPosition({200.f, 200.f});
}
