//
// Created by olafv on 12/13/2022.
//

#include "MainMenuScene.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/MenuScripts/StartGameButtonScript.h"
#include "../scripts/MenuScripts/SelectLevelButtonScript.h"
#include "../scripts/MenuScripts/SettingsButtonScript.h"
#include "../scripts/MenuScripts/ExitButtonScript.h"

void MainMenuScene::build(Scene& scene) const {


    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();

    auto& TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 34,
                                                                    rs->screenSizeHeight() / 100 * 8),
                                                      0, "Zombie Slayer",70, Color(),
                                                   "res/fonts/ZenDots-Regular.ttf",
                                                   Alignment::Center, false);

    auto& startGameButton = scene.createNewGameObject<Button>(root, 200, 100,
                                                              Vector2(rs->screenSizeWidth() / 2.0,
                                                                      rs->screenSizeHeight() / 3.0),true,
                                                                      "clickButton", Vector2(0, 0), 0,
                                                                      "Start game", 20, Color(),
                                                                      "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                      , Alignment::Center);
     StartGameButtonScript startGameScript;
     startGameScript.setParentGameObject(startGameButton);
     startGameButton.addComponent<StartGameButtonScript>(startGameScript);

     auto& selectLevelButton = scene.createNewGameObject<Button>(root,200, 100,
                                                               Vector2(rs->screenSizeWidth() / 2.0,
                                                                       rs->screenSizeHeight() / 2.0),true,
                                                                 "clickButton", Vector2(0, 0), 0,
                                                                 "Select level", 20, Color(),
                                                                 "res/fonts/Rubik-VariableFont_wght.ttf",
                                                                 Alignment::Center);
    SelectLevelButtonScript selectLevelScript;
    selectLevelScript.setParentGameObject(selectLevelButton);
    selectLevelButton.addComponent<SelectLevelButtonScript>(selectLevelScript);


     auto& settingsButton = scene.createNewGameObject<Button>(root,200, 100,
                                                                 Vector2(rs->screenSizeWidth() / 2.0,
                                                                         rs->screenSizeHeight() / 1.5),true,
                                                              "clickButton", Vector2(0, 0), 0,
                                                              "Settings", 20, Color(),
                                                              "res/fonts/Rubik-VariableFont_wght.ttf"
                                                              ,Alignment::Center);
    SettingsButtonScript settingsScript;
    settingsScript.setParentGameObject(settingsButton);
    settingsButton.addComponent<SettingsButtonScript>(settingsScript);

     auto& exitButton = scene.createNewGameObject<Button>(root,200, 100,
                                                                 Vector2(rs->screenSizeWidth() / 2.0,
                                                                         rs->screenSizeHeight() / 1.2),true,
                                                          "clickButton", Vector2(0, 0), 0,
                                                          "Exit", 20, Color(),
                                                          "res/fonts/Rubik-VariableFont_wght.ttf"
                                                          ,Alignment::Center);

    ExitButtonScript exitScript;
    settingsScript.setParentGameObject(exitButton);
    exitButton.addComponent<ExitButtonScript>(exitScript);


    auto& soldier = scene.createNewGameObject<GameObject>();
    soldier.addComponent<SpriteComponent>("res/sprites/soldier.png");
    soldier.setWorldTransform(Transform(Vector2(rs->screenSizeWidth() / 4.6,rs->screenSizeHeight() / 2.0),
                                   0, Vector2(1,1)));

    auto& zombieHand = scene.createNewGameObject<GameObject>();
    zombieHand.addComponent<SpriteComponent>("res/sprites/zombiehand.png");
    zombieHand.setWorldTransform(Transform(Vector2(rs->screenSizeWidth() / 1.2,rs->screenSizeHeight() / 2.0),
                                   0, Vector2(1,1)));

}