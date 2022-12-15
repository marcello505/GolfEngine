//
// Created by olafv on 12/13/2022.
//

#include <iomanip>
#include "SettingsScene.h"
#include "Core/GameLoop.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/BackButtonScript.h"
#include "../scripts/MasterVolumeButtonScript.h"
#include "Services/Singletons/AudioSingleton.h"
#include "../scripts/FullScreenButtonScript.h"
#include "../scripts/SoundEffectVolumeButtonScript.h"
#include "../scripts/MusicVolumeButtonScript.h"
#include "../scripts/KeyConfigButtonScript.h"

void SettingsScene::build(Scene& scene) const {

    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();
    auto* _audioService = GolfEngine::Services::Audio::getService();
    auto* actionMap = ActionMap::getActionMap();

    BackButtonScript backScript;
    auto& backButton = scene.createNewGameObject<Button>(root, 150, 70,
                                                         Vector2(rs->screenSizeWidth() /
                                                                 100.0 * 12.0,
                                                                 rs->screenSizeHeight() /
                                                                 100.0 * 12.0), 0,
                                                         "clickButton", Vector2(0,0 ), true,
                                                         "Back", 20, Color(),
                                                         R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)",
                                                         Alignment::Center);
    backScript.setParentGameObject(backButton);
    backButton.addComponent<BackButtonScript>(backScript);

    auto& titleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 40,
                                                                    rs->screenSizeHeight() / 100 * 8),
                                                      0, "Settings",70, Color(),
                                                      R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                      Alignment::Center, false);

    auto& volumeTitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 20,
                                                                          rs->screenSizeHeight() / 3.5),0,
                                                                          "Volume",50, Color(),
                                                                          R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                          Alignment::Center, false);

    // master

    auto& masterVolumeText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 13,
                                                                     rs->screenSizeHeight() / 2.3),0, "Master: ",20,
                                                       Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                       Alignment::Center, false);


    std::string currentMasterVolume = std::to_string((int)(_audioService->getMasterVolume() *10) * 10);

    auto& masterVolumeValueText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 26,
                                                                     rs->screenSizeHeight() / 2.3),0, currentMasterVolume,20,
                                                            Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                            Alignment::Center, false);

    auto& volumeTextUpdateScriptMaster =
            masterVolumeValueText.addComponent<VolumeTextUpdateScript>(&masterVolumeValueText);
    volumeTextUpdateScriptMaster.setParentGameObject(masterVolumeValueText);
    masterVolumeValueText.addComponent<VolumeTextUpdateScript>(volumeTextUpdateScriptMaster);

    auto masterVolumeScript = MasterVolumeButtonScript(&volumeTextUpdateScriptMaster);

    auto& masterVolumeDownButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                               Vector2(rs->screenSizeWidth() / 100 * 22,
                                                                       rs->screenSizeHeight() / 2.25),true,
                                                               "clickButton", Vector2(0, 0), 0,
                                                               "-", 60, Color(),
                                                               R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                               ,Alignment::Center);
    masterVolumeScript.setParentGameObject(masterVolumeDownButton);
    masterVolumeDownButton.addComponent<MasterVolumeButtonScript>(masterVolumeScript);


    auto& masterVolumeUpButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                               Vector2(rs->screenSizeWidth() / 100 * 33,
                                                                       rs->screenSizeHeight() / 2.25),true,
                                                               "clickButton", Vector2(0, 0), 0,
                                                               "+", 50, Color(),
                                                               R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                               ,Alignment::Center);
    masterVolumeScript.setParentGameObject(masterVolumeUpButton);
    masterVolumeUpButton.addComponent<MasterVolumeButtonScript>(masterVolumeScript);


    //soundEffect

    auto& soundEffectVolumeText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 13,
                                                                           rs->screenSizeHeight() / 1.83),0,
                                                                  "Sound: ",20,
                                                                  Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                 Alignment::Center, false);



    std::string currentSoundEffectVolume = std::to_string((int)(_audioService->getSfxVolume() *10) * 10);

    auto& soundEffectVolumeValueText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 26,
                                                                                     rs->screenSizeHeight() / 1.83),0, currentSoundEffectVolume,20,
                                                                  Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                  Alignment::Center, false);

    auto& volumeTextUpdateScriptSoundEffect =
            soundEffectVolumeValueText.addComponent<VolumeTextUpdateScript>(&soundEffectVolumeValueText);
    volumeTextUpdateScriptSoundEffect.setParentGameObject(soundEffectVolumeValueText);
    soundEffectVolumeValueText.addComponent<VolumeTextUpdateScript>(volumeTextUpdateScriptSoundEffect);

    auto soundEffectVolumeScript = SoundEffectVolumeButtonScript(&volumeTextUpdateScriptSoundEffect);

    auto& soundEffectVolumeDownButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                               Vector2(rs->screenSizeWidth() / 100 * 22,
                                                                       rs->screenSizeHeight() / 1.8),true,
                                                               "clickButton", Vector2(0, 0), 0,
                                                               "-", 60, Color(),
                                                               R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                ,Alignment::Center);
    soundEffectVolumeScript.setParentGameObject(soundEffectVolumeDownButton);
    soundEffectVolumeDownButton.addComponent<SoundEffectVolumeButtonScript>(soundEffectVolumeScript);

    auto& soundEffectVolumeUpButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                             Vector2(rs->screenSizeWidth() / 100 * 33,
                                                                     rs->screenSizeHeight() / 1.8),true,
                                                             "clickButton", Vector2(0, 0), 0,
                                                             "+", 50, Color(),
                                                             R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                             ,Alignment::Center);
    soundEffectVolumeScript.setParentGameObject(soundEffectVolumeUpButton);
    soundEffectVolumeUpButton.addComponent<SoundEffectVolumeButtonScript>(soundEffectVolumeScript);

    //music

    auto& musicVolumeText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 13,
                                                                                rs->screenSizeHeight() / 1.49),0,
                                                                  "Sound: ",20,
                                                                  Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                  Alignment::Center, false);



    std::string currentMusicVolume = std::to_string((int)(_audioService->getSfxVolume() *10) * 10);

    auto& musicVolumeValueText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 26,
                                                                                     rs->screenSizeHeight() / 1.49),0, currentMusicVolume,20,
                                                                       Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                       Alignment::Center, false);

    auto& volumeTextUpdateScriptMusic =
            musicVolumeValueText.addComponent<VolumeTextUpdateScript>(&musicVolumeValueText);
    volumeTextUpdateScriptMusic.setParentGameObject(musicVolumeValueText);
    musicVolumeValueText.addComponent<VolumeTextUpdateScript>(volumeTextUpdateScriptMusic);

    auto musicVolumeScript = MusicVolumeButtonScript(&volumeTextUpdateScriptMusic);

    auto& musicVolumeDownButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                                          Vector2(rs->screenSizeWidth() / 100 * 22,
                                                                                  rs->screenSizeHeight() / 1.47),true,
                                                                          "clickButton", Vector2(0, 0), 0,
                                                                          "-", 60, Color(),
                                                                          R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                          ,Alignment::Center);
    musicVolumeScript.setParentGameObject(musicVolumeDownButton);
    musicVolumeDownButton.addComponent<MusicVolumeButtonScript>(musicVolumeScript);

    auto& musicVolumeUpButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                                        Vector2(rs->screenSizeWidth() / 100 * 33,
                                                                                rs->screenSizeHeight() / 1.47),true,
                                                                        "clickButton", Vector2(0, 0), 0,
                                                                        "+", 50, Color(),
                                                                        R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                        ,Alignment::Center);
    musicVolumeScript.setParentGameObject(musicVolumeUpButton);
    musicVolumeUpButton.addComponent<MusicVolumeButtonScript>(musicVolumeScript);


    auto& fullScreenTitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 2.45,
                                                                              rs->screenSizeHeight() / 3.5),0,
                                                                "Fullscreen",50, Color(),
                                                                R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                Alignment::Center, false);

    FullScreenButtonScript fullScreenScript;
    auto& FullScreenButton = scene.createNewGameObject<Button>(root, 200, 100,
                                                             Vector2(rs->screenSizeWidth() / 2.05,
                                                                     rs->screenSizeHeight() / 1.9),true,
                                                             "clickButton", Vector2(0, 0), 0,
                                                             "Toggle full screen", 20, Color(),
                                                             R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                             ,Alignment::Center);
    fullScreenScript.setParentGameObject(FullScreenButton);
    FullScreenButton.addComponent<FullScreenButtonScript>(fullScreenScript);


    auto& keyConfigTitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 1.5,
                                                                              rs->screenSizeHeight() / 3.5),0,
                                                                "Key config",50, Color(),
                                                                R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                                Alignment::Center, false);





    //playerleft
    auto& playerLeftKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 70,
                                                                          rs->screenSizeHeight() / 2.3),0,
                                                            "playerLeft" ,20,
                                                            Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                            Alignment::Center, false);

    auto& playerLeftKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                     Vector2(rs->screenSizeWidth() / 100 * 82,
                                                                             rs->screenSizeHeight() / 2.25),true,
                                                                     "clickButton", Vector2(0, 0), 0,
                                                                     "Change key", 20, Color(),
                                                                     R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                    ,Alignment::Center);

    auto& keyConfigScript =
            playerLeftKeyButton.addComponent<KeyConfigButtonScript>("playerLeft");
    keyConfigScript.setParentGameObject(playerLeftKeyButton);
    playerLeftKeyButton.addComponent<KeyConfigButtonScript>(keyConfigScript);


    //playerRight
    auto& playerRightKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 70,
                                                                            rs->screenSizeHeight() / 2.0),0,
                                                              "playerRight" ,20,
                                                              Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                              Alignment::Center, false);

    auto& playerRightKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                  Vector2(rs->screenSizeWidth() / 100 * 82,
                                                                          rs->screenSizeHeight() / 1.95),true,
                                                                  "clickButton", Vector2(0, 0), 0,
                                                                  "Change key", 20, Color(),
                                                                  R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                  ,Alignment::Center);

    //playerUp
    auto& playerUpKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 70,
                                                                             rs->screenSizeHeight() / 1.77),0,
                                                               "playerUp" ,20,
                                                               Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                               Alignment::Center, false);

    auto& playerUpKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                   Vector2(rs->screenSizeWidth() / 100 * 82,
                                                                           rs->screenSizeHeight() / 1.73),true,
                                                                   "clickButton", Vector2(0, 0), 0,
                                                                   "Change key", 20, Color(),
                                                                   R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                   ,Alignment::Center);

    //playerDown
    auto& playerDownKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 70,
                                                                          rs->screenSizeHeight() / 1.58),0,
                                                            "playerDown" ,20,
                                                            Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                            Alignment::Center, false);

    auto& playerDownKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                Vector2(rs->screenSizeWidth() / 100 * 82,
                                                                        rs->screenSizeHeight() / 1.55),true,
                                                                "clickButton", Vector2(0, 0), 0,
                                                                "Change key", 20, Color(),
                                                                R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                ,Alignment::Center);


    //playerShoot
    auto& playerShootKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 70,
                                                                            rs->screenSizeHeight() / 1.43),0,
                                                              "playerShoot" ,20,
                                                              Color(), R"(../../game/res/fonts/ZenDots-Regular.ttf)",
                                                              Alignment::Center, false);

    auto& playerShootKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                  Vector2(rs->screenSizeWidth() / 100 * 82,
                                                                          rs->screenSizeHeight() / 1.40),true,
                                                                  "clickButton", Vector2(0, 0), 0,
                                                                  "Change key", 20, Color(),
                                                                  R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                                  ,Alignment::Center);

}