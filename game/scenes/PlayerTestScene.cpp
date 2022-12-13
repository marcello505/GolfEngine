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
#include "../gameobjects/TestBlock.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/BoxCollider.h"

void PlayerTestScene::build(Scene& scene) const {
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

    auto& testArea = scene.createNewGameObject<GameObject>();
    testArea.addComponent<BoxCollider>(Vector2{50.0f, 50.0f});
    testArea.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::AreaBody});
    testArea.tag = "finish";
    testArea.setLocalPosition({1000.0f, 100.0f});
}
