//
// Created by olafv on 12/13/2022.
//

#include "SettingsScene.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/BackButtonScript.h"
#include "../scripts/VolumeButtonScript.h"
#include "Services/Singletons/AudioSingleton.h"
#include "../scripts/FullScreenButtonScript.h"

void SettingsScene::build(Scene& scene) const {

    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    BackButtonScript backScript;
    auto& backButton = scene.createNewGameObject<Button>(root, 150, 70,
                                                         Vector2(100,90) ,true,
                                                         "clickButton", Vector2(rs->screenSizeWidth() /
                                                                                100 * 3,
                                                                                rs->screenSizeHeight() /100 * 9.0), 0,
                                                         "Back", 20, Color(),
                                                         R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)",
                                                         Alignment::Center);
    backScript.setParentGameObject(backButton);
    backButton.addComponent<BackButtonScript>(backScript);

    auto& TitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 2.8,
                                                                    rs->screenSizeHeight() / 100 * 8),
                                                      0, "Settings",70, Color(),
                                                      R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                      Alignment::Center, false);

    auto& VolumeTitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 2.4,
                                                                          rs->screenSizeHeight() / 3.5),0,
                                                                          "Volume",50, Color(),
                                                                          R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                          Alignment::Center, false);

    VolumeButtonScript volumeScript;

    auto& VolumeDownButton = scene.createNewGameObject<Button>(root, 150, 50,
                                                              Vector2(rs->screenSizeWidth() / 2.9,
                                                                      rs->screenSizeHeight() / 2.2),true,
                                                              "clickButton", Vector2(0, 0), 0,
                                                              "-", 60, Color(),
                                                              R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                              ,Alignment::Center);
    volumeScript.setParentGameObject(VolumeDownButton);
    VolumeDownButton.addComponent<VolumeButtonScript>(volumeScript);

    std::string currentVolume = std::to_string(_audioService->getMasterVolume());

    auto& VolumeText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 2.35,
                                                                     rs->screenSizeHeight() / 2.3),0, currentVolume,30,
                                                            Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                            Alignment::Center, false);

    auto& VolumeUpButton = scene.createNewGameObject<Button>(root, 150, 50,
                                                               Vector2(rs->screenSizeWidth() / 1.5,
                                                                       rs->screenSizeHeight() / 2.2),true,
                                                               "clickButton", Vector2(0, 0), 0,
                                                               "+", 50, Color(),
                                                               R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                               ,Alignment::Center);
    volumeScript.setParentGameObject(VolumeUpButton);
    VolumeUpButton.addComponent<VolumeButtonScript>(volumeScript);


    FullScreenButtonScript fullScreenScript;
    auto& FullScreenButton = scene.createNewGameObject<Button>(root, 200, 100,
                                                             Vector2(rs->screenSizeWidth() / 2,
                                                                     rs->screenSizeHeight() / 1.5),true,
                                                             "clickButton", Vector2(0, 0), 0,
                                                             "Toggle full screen", 20, Color(),
                                                             R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                             ,Alignment::Center);
    fullScreenScript.setParentGameObject(FullScreenButton);
    FullScreenButton.addComponent<FullScreenButtonScript>(fullScreenScript);

}