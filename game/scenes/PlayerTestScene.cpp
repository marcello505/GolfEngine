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
#include "../scripts/MenuScripts/BackButtonScript.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/RenderSingleton.h"

void PlayerTestScene::build(Scene& scene) const {

    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();
    root.addComponent<SaveStateScript>();

    BackButtonScript backScript;
    auto& backButton = scene.createNewGameObject<Button>(root, 45, 26,
                                                         Vector2(rs->screenSizeWidth() / 100 * 4,
                                                                 rs->screenSizeHeight() / 100 * 1.8) ,true,
                                                         "clickButton", Vector2(0, 0), 0,
                                                         "Back", 15, Color(),
                                                         R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)",
                                                         Alignment::Center);
    backScript.setParentGameObject(backButton);
    backButton.addComponent<BackButtonScript>(backScript);

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

    //Objects
    {
        scene.createNewGameObject<TestBlock>(root, Vector2{200.0f, 500.0f});
        scene.createNewGameObject<TestBlock>(root, Vector2{100.0f, 250.0f});
        scene.createNewGameObject<TestBlock>(root, Vector2{312.0f, 346.0f});

    }

    auto& projectilePool = scene.createNewGameObject<ProjectilePoolObject>(root, std::ref(scene), 20);

    auto& player = scene.createNewGameObject<PlayerObject>(root, &projectilePool.getComponent<ProjectilePoolScript>());
    player.setLocalPosition({200.f, 200.f});
}
