//
// Created by olafv on 12/13/2022.
//

#include "SelectLevelScene.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/MenuScripts/StartGameButtonScript.h"
#include "../scripts/MenuScripts/BackButtonScript.h"

using namespace GolfEngine::Scene::UI;

void SelectLevelScene::build(Scene& scene) const {


    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();

    BackButtonScript backScript;

    auto& backButton = scene.createNewGameObject<Button>(root, 150, 70,
                                                                  Vector2(rs->screenSizeWidth() /
                                                                          100.0 * 12.0,
                                                                          rs->screenSizeHeight() /
                                                                            100.0 * 12.0), 0,
                                                                  "clickButton", Vector2(0,0 ), true,
                                                                  "Back", 20, Color(),
                                                                  "res/fonts/Rubik-VariableFont_wght.ttf",
                                                                  Alignment::Center);
    backScript.setParentGameObject(backButton);
    backButton.addComponent<BackButtonScript>(backScript);


    auto& TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100.0 * 35.0,
                                                                    rs->screenSizeHeight() / 100.0 * 8.0),
                                                      0, "Select Level",70, Color(),
                                                      "res/fonts/ZenDots-Regular.ttf",
                                                      Alignment::Center, false);

    StartGameButtonScript script;

    auto& startLevelOneButton = scene.createNewGameObject<Button>(root, 302, 210,
                                                              Vector2(rs->screenSizeWidth() / 5.0,
                                                                      rs->screenSizeHeight() / 2.0) ,true,
                                                                      "clickButton", Vector2(0, 0), 0,
                                                                      "1", 20, Color(),
                                                                      "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                      ,Alignment::Center);
    startLevelOneButton.name = "level1";

    script.setParentGameObject(startLevelOneButton);
    startLevelOneButton.addComponent<StartGameButtonScript>(script);

    auto& startLevelOneImage = scene.createNewGameObject<GameObject>();
    startLevelOneImage.addComponent<SpriteComponent>("res/sprites/level1.png");

    startLevelOneImage.setWorldTransform(Transform(Vector2(rs->screenSizeWidth() / 5.0,rs->screenSizeHeight() / 2.0),
                                   0, Vector2(1,1)));



    auto& startLevelTwoButton = scene.createNewGameObject<Button>(root, 302, 210,
                                                                  Vector2(rs->screenSizeWidth() / 2,
                                                                          rs->screenSizeHeight() / 2.0) ,true,
                                                                  "clickButton", Vector2(0, 0), 0,
                                                                  "2", 20, Color(),
                                                                  "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                  ,Alignment::Center);
    startLevelTwoButton.name = "level2";

    script.setParentGameObject(startLevelTwoButton);
    startLevelTwoButton.addComponent<StartGameButtonScript>(script);

    auto& startLevelTwoImage = scene.createNewGameObject<GameObject>();
    startLevelTwoImage.addComponent<SpriteComponent>("res/sprites/level2.png");
    startLevelTwoImage.setWorldTransform(Transform(Vector2(rs->screenSizeWidth() / 2,
                                                           rs->screenSizeHeight() / 2.0), 0, Vector2(1,1)));



    auto& startLevelThreeButton = scene.createNewGameObject<Button>(root, 302, 210,
                                                                  Vector2(rs->screenSizeWidth() / 1.25,
                                                                          rs->screenSizeHeight() / 2.0) ,true,
                                                                  "clickButton", Vector2(0, 0), 0,
                                                                  "3", 20, Color(),
                                                                  "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                  ,Alignment::Center);
    startLevelThreeButton.name = "playerTest";

    script.setParentGameObject(startLevelThreeButton);
    startLevelThreeButton.addComponent<StartGameButtonScript>(script);

    auto& startLevelThreeImage = scene.createNewGameObject<GameObject>();
    startLevelThreeImage.addComponent<SpriteComponent>("res/sprites/level3.png");
    startLevelThreeImage.setWorldTransform(Transform(Vector2(rs->screenSizeWidth() / 1.25,
                                                                     rs->screenSizeHeight() / 2.0),
                                                                    0, Vector2(1,1)));

}