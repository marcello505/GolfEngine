//
// Created by olafv on 12/18/2022.
//

#include "YouWonScene.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/MenuScripts/BackButtonScript.h"
#include "Scene/Components/AudioSource.h"

void YouWonScene::build(Scene& scene) const {


    auto *rs = GolfEngine::Services::Render::getService();
    auto &root = scene.createNewGameObject<GameObject>();
    auto& levelMusic = root.addComponent<GolfEngine::Scene::Components::AudioSource>(true, true, false);
    levelMusic.addSound("youWin", "res/music/martian_blues.mp3");
    levelMusic.volume = 0.3f;

    auto &TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 20,
                                                                    rs->screenSizeHeight() / 100 * 8),
                                                      0, "You slayed all the zombies!", 70, Color(),
                                                      "res/fonts/ZenDots-Regular.ttf",
                                                      Alignment::Center, false);

    auto &backButton = scene.createNewGameObject<Button>(root, 150, 100,
                                                         Vector2(rs->screenSizeWidth() / 2,
                                                                 rs->screenSizeHeight() / 1.5), 0,
                                                         "clickButton", Vector2(0, 0), true,
                                                         "Back to menu", 20, Color(),
                                                         "res/fonts/Rubik-VariableFont_wght.ttf",
                                                         Alignment::Center);

    BackButtonScript backScript;
    backScript.setParentGameObject(backButton);
    backButton.addComponent<BackButtonScript>(backScript);

    auto& trophy = scene.createNewGameObject<GameObject>();
    trophy.addComponent<SpriteComponent>("res/sprites/trophy.png");
    trophy.setWorldTransform(Transform(Vector2( rs->screenSizeWidth() / 2.0,
                                                 rs->screenSizeHeight() / 2.8),
                                        0, Vector2(1,1)));
}