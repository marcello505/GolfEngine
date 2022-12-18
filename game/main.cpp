
// Engine includes
#include "Core/GameLoop.h"
#include "Core/Settings.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Utilities/IO.h"

// Game includes
#include "scenes/PlayerTestScene.h"

#include "scenes/MainMenuScene.h"
#include "scenes/SelectLevelScene.h"
#include "scenes/SettingsScene.h"

#include "scenes/SaveGameTestScene.h"
#include <SDL.h>

#define PROJECT_SETTINGS_SAVE_PATH "ProjectSettings.xml"


int main(int argc, char* argv[]){
    // Load project settings save file
    if(GolfEngine::Utilities::IO::userDataFileExists(PROJECT_SETTINGS_SAVE_PATH)){
        auto savedSettings = GolfEngine::Utilities::IO::loadSettings(PROJECT_SETTINGS_SAVE_PATH);
        GolfEngine::Core::getProjectSettings().fromXml(savedSettings.toXml());
    }

    GameLoop gameLoop {};
    gameLoop.useDefaultServices();

    //Render initialization
    GolfEngine::Services::Render::getService()->setScreenSize(1920, 1080);
    GolfEngine::Services::Render::getService()->setWindowTitle("Game name");

    // Init volume settings
    auto& volumeSettings = GolfEngine::Core::getProjectSettings();
    auto audioService = GolfEngine::Services::Audio::getService();
    if(volumeSettings.hasFloat("MasterVolume"))
        audioService->setMasterVolume(volumeSettings.getFloat("MasterVolume"));
    if(volumeSettings.hasFloat("MusicVolume"))
        audioService->setMusicVolume(volumeSettings.getFloat("MusicVolume"));
    if(volumeSettings.hasFloat("SFXVolume"))
        audioService->setSfxVolume(volumeSettings.getFloat("SFXVolume"));

    //Set up controls
    auto* actionMap = ActionMap::getActionMap();
    actionMap->addAction("playerLeft");
    actionMap->addInputKeyToAction("playerLeft", InputKey::Key_A);
    actionMap->addAction("playerRight");
    actionMap->addInputKeyToAction("playerRight", InputKey::Key_D);
    actionMap->addAction("playerUp");
    actionMap->addInputKeyToAction("playerUp", InputKey::Key_W);
    actionMap->addAction("playerDown");
    actionMap->addInputKeyToAction("playerDown", InputKey::Key_S);
    actionMap->addAction("playerShoot");
    actionMap->addInputKeyToAction("playerShoot", InputKey::Mouse_Left);
    actionMap->addAction("playerReload");
    actionMap->addInputKeyToAction("playerReload", InputKey::Key_R);
    actionMap->addAction("restart");
    actionMap->addInputKeyToAction("restart", InputKey::Key_Backspace);

    //Set up recording controls
    actionMap->addAction("startRecordingReplay");
    actionMap->addInputKeyToAction("startRecordingReplay", InputKey::Key_I);
    actionMap->addAction("stopRecordingReplay");
    actionMap->addInputKeyToAction("stopRecordingReplay", InputKey::Key_O);
    actionMap->addAction("playReplay");
    actionMap->addInputKeyToAction("playReplay", InputKey::Key_P);

    //Set up menu controls
    actionMap->addAction("clickButton");
    actionMap->addInputKeyToAction("clickButton", Mouse_Left);

    // Save Game actions
    actionMap->addAction("saveGame");
    actionMap->addInputKeyToAction("saveGame", InputKey::Key_K);
    actionMap->addAction("loadGame");
    actionMap->addInputKeyToAction("loadGame", InputKey::Key_L);

    // Render FPS
    actionMap->addAction("renderFPS");
    actionMap->addInputKeyToAction("renderFPS", Key_F9);

    //Debug settings
    GolfEngine::Core::getProjectSettings().setBool(PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS, true); //Render colliders
    GolfEngine::Core::getProjectSettings().setBool(PROJECT_SETTINGS_BOOL_RENDER_PATHFINDING, false); //Render pathfinding nodes

    //Scene initialization
    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    sceneManager.addScene<PlayerTestScene>("playerTest");
    sceneManager.addScene<SaveGameTestScene>("saveGameTest");
    sceneManager.addSceneFactory<MainMenuScene>("mainMenu");
    sceneManager.addSceneFactory<SelectLevelScene>("selectLevel");
    sceneManager.addSceneFactory<SettingsScene>("settings");
    sceneManager.loadScene("mainMenu");

    gameLoop.start();

    // Save project settings before closing the game
    auto projectSettings = GolfEngine::Core::getProjectSettings();
    GolfEngine::Utilities::IO::saveSettings(PROJECT_SETTINGS_SAVE_PATH, projectSettings);
    return 0;
}