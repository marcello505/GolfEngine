//
// Created by olafv on 12/13/2022.
//

#include "MainMenuScene.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/StartGameButtonScript.h"

void MainMenuScene::build(Scene& scene) const {


    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();

    auto& TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 4.0, 50),
                                                      0, "Zombie Slayer",70, Color(),
                                                   R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                   Alignment::Center, false);

    auto& startGameButton = scene.createNewGameObject<Button>(root, 200, 100,
                                                              Vector2(rs->screenSizeWidth() / 2.0,
                                                                      rs->screenSizeHeight() / 3.0),true,
                                                                      "clickButton", Vector2(0, 0), 0,
                                                                      "Start game", 20, Color(),
                                                                      R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                      , Alignment::Center);
     StartGameButtonScript script;
     script.setParentGameObject(startGameButton);
     startGameButton.addComponent<StartGameButtonScript>(script);



     auto& selectLevelButton = scene.createNewGameObject<Button>(root,200, 100,
                                                               Vector2(rs->screenSizeWidth() / 2.0,
                                                                       rs->screenSizeHeight() / 2.0),true,
                                                                 "clickButton", Vector2(0, 0), 0,
                                                                 "Start game", 20, Color(),
                                                                 R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)",
                                                                 Alignment::Center);


/*
     auto& settingsButton = scene.createNewGameObject<Button>(root,200, 100,
                                                                 Vector2(rs->screenSizeWidth() / 2.0,
                                                                         rs->screenSizeHeight() / 1.5),true,
                                                              "clickButton", Vector2(0, 0), 0,
                                                              "Start game", 20, Color(),
                                                              R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                              ,Alignment::Center);



     auto& exitButton = scene.createNewGameObject<Button>(root,200, 100,
                                                                 Vector2(rs->screenSizeWidth() / 2.0,
                                                                         rs->screenSizeHeight() / 1.2),true,
                                                          "clickButton", Vector2(0, 0), 0,
                                                          "Start game", 20, Color(),
                                                          R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                          ,Alignment::Center);*/

/*    auto& go = scene.createNewGameObject<GameObject>();
    go.addComponent<SpriteComponent>("res/sprites/soldier.png");
    go.setWorldTransform(Transform(Vector2(rs->screenSizeWidth() / 4.6,rs->screenSizeHeight() / 2.0),
                                   0, Vector2(1,1)));

    auto& go2 = scene.createNewGameObject<GameObject>();
    go2.addComponent<SpriteComponent>("res/sprites/zombiehand.png");
    go2.setWorldTransform(Transform(Vector2(rs->screenSizeWidth() / 1.2,rs->screenSizeHeight() / 2.0),
                                   0, Vector2(1,1)));*/

}