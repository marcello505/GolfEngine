//
// Created by olafv on 12/15/2022.
//

#include "KeyConfigScene.h"
#include "Services/Singletons/RenderSingleton.h"


void KeyConfigScene::build(Scene& scene) const {


    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();

    auto& TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 34,
                                                                    rs->screenSizeHeight() / 100 * 20),
                                                      0, "Press any key",80, Color(),
                                                      R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                      Alignment::Center, false);

}