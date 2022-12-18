//
// Created by olafv on 12/18/2022.
//

#include "YouWonScene.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/MenuScripts/BackButtonScript.h"

void YouWonScene::build(Scene& scene) const {


    auto *rs = GolfEngine::Services::Render::getService();
    auto &root = scene.createNewGameObject<GameObject>();

    auto &TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 34,
                                                                    rs->screenSizeHeight() / 100 * 8),
                                                      0, "You won!", 70, Color(),
                                                      "res/fonts/ZenDots-Regular.ttf",
                                                      Alignment::Center, false);

    auto &backButton = scene.createNewGameObject<Button>(root, 150, 100,
                                                         Vector2(rs->screenSizeWidth() /
                                                                 100.0 * 12.0,
                                                                 rs->screenSizeHeight() /
                                                                 100.0 * 12.0), 0,
                                                         "clickButton", Vector2(0, 0), true,
                                                         "Back to menu", 20, Color(),
                                                         "res/fonts/Rubik-VariableFont_wght.ttf",
                                                         Alignment::Center);
}