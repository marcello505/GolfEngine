//
// Created by olafv on 12/13/2022.
//

#include "MainMenuScene.h"
#include "Services/Singletons/RenderSingleton.h"

void MainMenuScene::build(Scene& scene) const {

    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();

/*    auto& TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 2, 10), 0, "Hotline Miami",
                                                   70, Color(),
                                                   R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)",
                                                   Alignment::Center, false);*/


    auto& text = scene.createNewGameObject<Text>(root, Vector2(0, 0), 0, "Start game",
                                                          20, Color(),
                                                          R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)",
                                                          Alignment::Center, true);


    auto& startGameButton = scene.createNewGameObject<Button>(root,200, 160,
                                                              Vector2(rs->screenSizeWidth() / 2,
                                                                      rs->screenSizeHeight() / 3), true, &text );

  /*  auto selectLevelText = new Text(Vector2(0, 0), 0, "Start game",
                                  20, Color(),
                                  R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)",
                                  Alignment::Center, true);
*/
/*    scene.createNewGameObject<Button>(root, 200, 160, Vector2(rs->screenSizeWidth() / 2,
                                                                      rs->screenSizeHeight() / 3), true, selectLevelText);*/
}