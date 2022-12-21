//
// Created by olafv on 12/13/2022.
//

#include <iomanip>
#include "SettingsScene.h"
#include "Core/GameLoop.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/SpriteComponent.h"
#include "../scripts/MenuScripts/BackButtonScript.h"
#include "../scripts/MenuScripts/MasterVolumeButtonScript.h"
#include "Services/Singletons/AudioSingleton.h"
#include "../scripts/MenuScripts/FullScreenButtonScript.h"
#include "../scripts/MenuScripts/SoundEffectVolumeButtonScript.h"
#include "../scripts/MenuScripts/MusicVolumeButtonScript.h"
#include "../scripts/MenuScripts/KeyConfigButtonScript.h"
#include "Services/Singletons/InputSingleton.h"

using namespace GolfEngine::Scene::UI;

void SettingsScene::build(Scene& scene) const {

    auto* rs = GolfEngine::Services::Render::getService();
    auto& root = scene.createNewGameObject<GameObject>();
    auto* _audioService = GolfEngine::Services::Audio::getService();
    auto* inputService = GolfEngine::Services::Input::getService();
    auto* actionMap = ActionMap::getActionMap();

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

    auto& titleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 40,
                                                                    rs->screenSizeHeight() / 100 * 8),
                                                      0, "Settings",70, Color(),
                                                      "res/fonts/ZenDots-Regular.ttf",
                                                      Alignment::Center, false);

    auto& volumeTitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 20,
                                                                          rs->screenSizeHeight() / 3.5),0,
                                                                          "Volume",50, Color(),
                                                                          "res/fonts/ZenDots-Regular.ttf",
                                                                          Alignment::Center, false);

    // master

    auto& masterVolumeText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 13,
                                                                     rs->screenSizeHeight() / 2.3),0, "Master: ",20,
                                                       Color(), "res/fonts/ZenDots-Regular.ttf",
                                                       Alignment::Center, false);


    std::string currentMasterVolume = std::to_string(GolfEngine::Utilities::Math::roundToNearestMultiple((int)(_audioService->getMasterVolume() * 100), 5));

    auto& masterVolumeValueText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 26,
                                                                     rs->screenSizeHeight() / 2.3),0, currentMasterVolume,20,
                                                            Color(), "res/fonts/ZenDots-Regular.ttf",
                                                            Alignment::Center, false);

    auto& volumeTextUpdateScriptMaster =
            masterVolumeValueText.addComponent<TextUpdateScript>(&masterVolumeValueText);
    volumeTextUpdateScriptMaster.setParentGameObject(masterVolumeValueText);
    masterVolumeValueText.addComponent<TextUpdateScript>(volumeTextUpdateScriptMaster);

    auto masterVolumeScript = MasterVolumeButtonScript(&volumeTextUpdateScriptMaster);

    auto& masterVolumeDownButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                               Vector2(rs->screenSizeWidth() / 100 * 22,
                                                                       rs->screenSizeHeight() / 2.25),true,
                                                               "clickButton", Vector2(0, 0), 0,
                                                               "-", 60, Color(),
                                                               "res/fonts/Rubik-VariableFont_wght.ttf"
                                                               ,Alignment::Center);
    masterVolumeScript.setParentGameObject(masterVolumeDownButton);
    masterVolumeDownButton.addComponent<MasterVolumeButtonScript>(masterVolumeScript);


    auto& masterVolumeUpButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                               Vector2(rs->screenSizeWidth() / 100 * 33,
                                                                       rs->screenSizeHeight() / 2.25),true,
                                                               "clickButton", Vector2(0, 0), 0,
                                                               "+", 50, Color(),
                                                               "res/fonts/Rubik-VariableFont_wght.ttf"
                                                               ,Alignment::Center);
    masterVolumeScript.setParentGameObject(masterVolumeUpButton);
    masterVolumeUpButton.addComponent<MasterVolumeButtonScript>(masterVolumeScript);


    //soundEffect

    auto& soundEffectVolumeText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 13,
                                                                           rs->screenSizeHeight() / 1.83),0,
                                                                  "Sound: ",20,
                                                                  Color(), "res/fonts/ZenDots-Regular.ttf",
                                                                 Alignment::Center, false);



    std::string currentSoundEffectVolume = std::to_string(GolfEngine::Utilities::Math::roundToNearestMultiple((int)(_audioService->getSfxVolume() * 100), 5));

    auto& soundEffectVolumeValueText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 26,
                                                                                     rs->screenSizeHeight() / 1.83),0, currentSoundEffectVolume,20,
                                                                  Color(), "res/fonts/ZenDots-Regular.ttf",
                                                                  Alignment::Center, false);

    auto& volumeTextUpdateScriptSoundEffect =
            soundEffectVolumeValueText.addComponent<TextUpdateScript>(&soundEffectVolumeValueText);
    volumeTextUpdateScriptSoundEffect.setParentGameObject(soundEffectVolumeValueText);
    soundEffectVolumeValueText.addComponent<TextUpdateScript>(volumeTextUpdateScriptSoundEffect);

    auto soundEffectVolumeScript = SoundEffectVolumeButtonScript(&volumeTextUpdateScriptSoundEffect);

    auto& soundEffectVolumeDownButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                               Vector2(rs->screenSizeWidth() / 100 * 22,
                                                                       rs->screenSizeHeight() / 1.8),true,
                                                               "clickButton", Vector2(0, 0), 0,
                                                               "-", 60, Color(),
                                                               "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                ,Alignment::Center);
    soundEffectVolumeScript.setParentGameObject(soundEffectVolumeDownButton);
    soundEffectVolumeDownButton.addComponent<SoundEffectVolumeButtonScript>(soundEffectVolumeScript);

    auto& soundEffectVolumeUpButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                             Vector2(rs->screenSizeWidth() / 100 * 33,
                                                                     rs->screenSizeHeight() / 1.8),true,
                                                             "clickButton", Vector2(0, 0), 0,
                                                             "+", 50, Color(),
                                                             "res/fonts/Rubik-VariableFont_wght.ttf"
                                                             ,Alignment::Center);
    soundEffectVolumeScript.setParentGameObject(soundEffectVolumeUpButton);
    soundEffectVolumeUpButton.addComponent<SoundEffectVolumeButtonScript>(soundEffectVolumeScript);

    //music

    auto& musicVolumeText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 13,
                                                                                rs->screenSizeHeight() / 1.49),0,
                                                                  "Music: ",20,
                                                                  Color(), "res/fonts/ZenDots-Regular.ttf",
                                                                  Alignment::Center, false);



    std::string currentMusicVolume = std::to_string(GolfEngine::Utilities::Math::roundToNearestMultiple((int)(_audioService->getMusicVolume() * 100), 5));

    auto& musicVolumeValueText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 26,
                                                                                     rs->screenSizeHeight() / 1.49),0, currentMusicVolume,20,
                                                                       Color(), "res/fonts/ZenDots-Regular.ttf",
                                                                       Alignment::Center, false);

    auto& volumeTextUpdateScriptMusic =
            musicVolumeValueText.addComponent<TextUpdateScript>(&musicVolumeValueText);
    volumeTextUpdateScriptMusic.setParentGameObject(musicVolumeValueText);
    musicVolumeValueText.addComponent<TextUpdateScript>(volumeTextUpdateScriptMusic);

    auto musicVolumeScript = MusicVolumeButtonScript(&volumeTextUpdateScriptMusic);

    auto& musicVolumeDownButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                                          Vector2(rs->screenSizeWidth() / 100 * 22,
                                                                                  rs->screenSizeHeight() / 1.47),true,
                                                                          "clickButton", Vector2(0, 0), 0,
                                                                          "-", 60, Color(),
                                                                          "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                          ,Alignment::Center);
    musicVolumeScript.setParentGameObject(musicVolumeDownButton);
    musicVolumeDownButton.addComponent<MusicVolumeButtonScript>(musicVolumeScript);

    auto& musicVolumeUpButton = scene.createNewGameObject<Button>(root, 100, 30,
                                                                        Vector2(rs->screenSizeWidth() / 100 * 33,
                                                                                rs->screenSizeHeight() / 1.47),true,
                                                                        "clickButton", Vector2(0, 0), 0,
                                                                        "+", 50, Color(),
                                                                        "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                        ,Alignment::Center);
    musicVolumeScript.setParentGameObject(musicVolumeUpButton);
    musicVolumeUpButton.addComponent<MusicVolumeButtonScript>(musicVolumeScript);


    auto& fullScreenTitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 2.45,
                                                                              rs->screenSizeHeight() / 3.5),0,
                                                                "Fullscreen",50, Color(),
                                                                "res/fonts/ZenDots-Regular.ttf",
                                                                Alignment::Center, false);

    //fullscreen
    FullScreenButtonScript fullScreenScript;
    auto& FullScreenButton = scene.createNewGameObject<Button>(root, 200, 100,
                                                             Vector2(rs->screenSizeWidth() / 2.05,
                                                                     rs->screenSizeHeight() / 1.9),true,
                                                             "clickButton", Vector2(0, 0), 0,
                                                             "Toggle full screen", 20, Color(),
                                                             "res/fonts/Rubik-VariableFont_wght.ttf"
                                                             ,Alignment::Center);
    fullScreenScript.setParentGameObject(FullScreenButton);
    FullScreenButton.addComponent<FullScreenButtonScript>(fullScreenScript);


    auto& keyConfigTitleText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 1.5,
                                                                              rs->screenSizeHeight() / 3.5),0,
                                                                "Key config",50, Color(),
                                                                "res/fonts/ZenDots-Regular.ttf",
                                                                Alignment::Center, false);





    //playerleft

    std::string playerLeftInputKey = inputService->getKeyString(actionMap->getActionKeys("playerLeft")[0]);


    auto& playerLeftKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 63,
                                                                          rs->screenSizeHeight() / 2.3),0,
                                                            "playerLeft ( " + playerLeftInputKey + " )" ,20,
                                                            Color(), "res/fonts/ZenDots-Regular.ttf",
                                                            Alignment::Center, false);

    auto& playerLeftTextUpdateScript =
            playerLeftKeyText.addComponent<TextUpdateScript>(&playerLeftKeyText);
    playerLeftTextUpdateScript.setParentGameObject(playerLeftKeyText);
    playerLeftKeyText.addComponent<TextUpdateScript>(playerLeftTextUpdateScript);

    auto& playerLeftKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                     Vector2(rs->screenSizeWidth() / 100 * 85,
                                                                             rs->screenSizeHeight() / 2.25),true,
                                                                     "clickButton", Vector2(0, 0), 0,
                                                                     "Change key", 20, Color(),
                                                                     "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                    ,Alignment::Center);

    auto keyConfigScriptPlayerLeft = KeyConfigButtonScript("playerLeft", &playerLeftTextUpdateScript);
    keyConfigScriptPlayerLeft.setParentGameObject(playerLeftKeyButton);
    playerLeftKeyButton.addComponent<KeyConfigButtonScript>(keyConfigScriptPlayerLeft);

    //playerRight

    std::string playerRightInputKey = inputService->getKeyString(actionMap->getActionKeys("playerRight")[0]);

    auto& playerRightKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 63,
                                                                            rs->screenSizeHeight() / 2.0),0,
                                                              "playerRight ( " + playerRightInputKey + " )" ,20,
                                                              Color(), "res/fonts/ZenDots-Regular.ttf",
                                                              Alignment::Center, false);

    auto& playerRightTextUpdateScript =
            playerRightKeyText.addComponent<TextUpdateScript>(&playerRightKeyText);
    playerRightTextUpdateScript.setParentGameObject(playerRightKeyText);
    playerRightKeyText.addComponent<TextUpdateScript>(playerRightTextUpdateScript);

    auto& playerRightKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                  Vector2(rs->screenSizeWidth() / 100 * 85,
                                                                          rs->screenSizeHeight() / 1.95),true,
                                                                  "clickButton", Vector2(0, 0), 0,
                                                                  "Change key", 20, Color(),
                                                                  "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                  ,Alignment::Center);

    auto keyConfigScriptPlayerRight = KeyConfigButtonScript("playerRight", &playerRightTextUpdateScript);
    keyConfigScriptPlayerRight.setParentGameObject(playerRightKeyButton);
    playerRightKeyButton.addComponent<KeyConfigButtonScript>(keyConfigScriptPlayerRight);

    //playerUp



    std::string playerUpInputKey = inputService->getKeyString(actionMap->getActionKeys("playerUp")[0]);

    auto& playerUpKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 63,
                                                                             rs->screenSizeHeight() / 1.77),0,
                                                            "playerUp ( " + playerUpInputKey + " )" ,20,
                                                               Color(), "res/fonts/ZenDots-Regular.ttf",
                                                               Alignment::Center, false);

    auto& playerUpTextUpdateScript =
            playerUpKeyText.addComponent<TextUpdateScript>(&playerUpKeyText);
    playerUpTextUpdateScript.setParentGameObject(playerUpKeyText);
    playerUpKeyText.addComponent<TextUpdateScript>(playerUpTextUpdateScript);


    auto& playerUpKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                   Vector2(rs->screenSizeWidth() / 100 * 85,
                                                                           rs->screenSizeHeight() / 1.73),true,
                                                                   "clickButton", Vector2(0, 0), 0,
                                                                   "Change key", 20, Color(),
                                                                   "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                   ,Alignment::Center);

    auto keyConfigScriptPlayerUp = KeyConfigButtonScript("playerUp", &playerUpTextUpdateScript);
    keyConfigScriptPlayerUp.setParentGameObject(playerUpKeyButton);
    playerUpKeyButton.addComponent<KeyConfigButtonScript>(keyConfigScriptPlayerUp);

    //playerDown

    std::string playerDownInputKey = inputService->getKeyString(actionMap->getActionKeys("playerDown")[0]);

    auto& playerDownKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 63,
                                                                          rs->screenSizeHeight() / 1.58),0,
                                                              "playerDown ( " + playerDownInputKey + " )"  ,20,
                                                            Color(), "res/fonts/ZenDots-Regular.ttf",
                                                            Alignment::Center, false);

    auto& playerDownTextUpdateScript =
            playerDownKeyText.addComponent<TextUpdateScript>(&playerDownKeyText);
    playerDownTextUpdateScript.setParentGameObject(playerDownKeyText);
    playerDownKeyText.addComponent<TextUpdateScript>(playerDownTextUpdateScript);

    auto& playerDownKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                Vector2(rs->screenSizeWidth() / 100 * 85,
                                                                        rs->screenSizeHeight() / 1.55),true,
                                                                "clickButton", Vector2(0, 0), 0,
                                                                "Change key", 20, Color(),
                                                                "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                ,Alignment::Center);

    auto keyConfigScriptPlayerDown = KeyConfigButtonScript("playerDown", &playerDownTextUpdateScript);
    keyConfigScriptPlayerDown.setParentGameObject(playerDownKeyButton);
    playerDownKeyButton.addComponent<KeyConfigButtonScript>(keyConfigScriptPlayerDown);

    //playerShoot

    std::string playerShootInputKey = inputService->getKeyString(actionMap->getActionKeys("playerShoot")[0]);

    auto& playerShootKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 63,
                                                                            rs->screenSizeHeight() / 1.43),0,
                                                               "playerShoot ( " + playerShootInputKey + " )"  ,20,
                                                              Color(), "res/fonts/ZenDots-Regular.ttf",
                                                              Alignment::Center, false);

    auto& playerShootTextUpdateScript =
            playerShootKeyText.addComponent<TextUpdateScript>(&playerShootKeyText);
    playerShootTextUpdateScript.setParentGameObject(playerShootKeyText);
    playerShootKeyText.addComponent<TextUpdateScript>(playerShootTextUpdateScript);

    auto& playerShootKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                  Vector2(rs->screenSizeWidth() / 100 * 85,
                                                                          rs->screenSizeHeight() / 1.40),true,
                                                                  "clickButton", Vector2(0, 0), 0,
                                                                  "Change key", 20, Color(),
                                                                  "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                  ,Alignment::Center);

    auto keyConfigScriptPlayerShoot = KeyConfigButtonScript("playerShoot", &playerShootTextUpdateScript);
    keyConfigScriptPlayerShoot.setParentGameObject(playerShootKeyButton);
    playerShootKeyButton.addComponent<KeyConfigButtonScript>(keyConfigScriptPlayerShoot);


    //playerReload

    std::string playerReloadInputKey = inputService->getKeyString(actionMap->getActionKeys("playerReload")[0]);

    auto& playerReloadKeyText = scene.createNewGameObject<Text>(root, Vector2(rs->screenSizeWidth() / 100 * 63,
                                                                             rs->screenSizeHeight() / 100 * 84),0,
                                                               "playerReload ( " + playerReloadInputKey + " )"  ,20,
                                                               Color(), "res/fonts/ZenDots-Regular.ttf",
                                                               Alignment::Center, false);

    auto& playerReloadTextUpdateScript =
            playerReloadKeyText.addComponent<TextUpdateScript>(&playerReloadKeyText);
    playerReloadTextUpdateScript.setParentGameObject(playerReloadKeyText);
    playerReloadKeyText.addComponent<TextUpdateScript>(playerReloadTextUpdateScript);

    auto& playerReloadKeyButton = scene.createNewGameObject<Button>(root, 120, 40,
                                                                   Vector2(rs->screenSizeWidth() / 100 * 85,
                                                                           rs->screenSizeHeight() / 100 * 85),true,
                                                                   "clickButton", Vector2(0, 0), 0,
                                                                   "Change key", 20, Color(),
                                                                   "res/fonts/Rubik-VariableFont_wght.ttf"
                                                                    ,Alignment::Center);

    auto keyConfigScriptPlayerReload = KeyConfigButtonScript("playerReload", &playerReloadTextUpdateScript);
    keyConfigScriptPlayerReload.setParentGameObject(playerReloadKeyButton);
    playerReloadKeyButton.addComponent<KeyConfigButtonScript>(keyConfigScriptPlayerReload);

}