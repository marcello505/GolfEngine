//
// Created by marcello on 11/29/22.
//

#include "PlayerTestScene.h"
#include "Scene/Components/RigidBody.h"
#include "../gameobjects/Player.h"
#include "../gameobjects/Wall.h"
#include "../gameobjects/Projectile.h"

void PlayerTestScene::build(Scene& scene) const {
    auto& root = scene.createNewGameObject<GameObject>();

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

    auto& player = scene.createNewGameObject<Player>(root);
    player.setLocalPosition({200.f, 200.f});

    scene.createNewGameObject<Projectile>().setLocalPosition({100.0f, 100.0f});
}