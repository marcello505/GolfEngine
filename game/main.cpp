
// Engine includes
#include "Core/GameLoop.h"
#include "Core/Settings.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Utilities/IO.h"

// Game includes
#include "utils/GameActions.h"
#include "utils/GameSettings.h"
#include "scenes/PlayerTestScene.h"
#include "scenes/Level2Scene.h"
#include "scenes/Level1Scene.h"

#include "scenes/MainMenuScene.h"
#include "scenes/SelectLevelScene.h"
#include "scenes/SettingsScene.h"

#include "scenes/YouWonScene.h"
#include "Scene/Components/AudioSource.h"
#include "scenes/SaveGameTestScene.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "scenes/Level3Scene.h"
#include <SDL.h>

#define PROJECT_SETTINGS_SAVE_PATH "ProjectSettings.xml"

using namespace GolfEngine::Core;

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
    GolfEngine::Services::Render::getService()->setWindowTitle("Zombie Slayer");

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
    actionMap->addAction(ACTION_PLAYER_LEFT);
    actionMap->addInputKeyToAction(ACTION_PLAYER_LEFT, InputKey::Key_A);
    actionMap->addAction(ACTION_PLAYER_RIGHT);
    actionMap->addInputKeyToAction(ACTION_PLAYER_RIGHT, InputKey::Key_D);
    actionMap->addAction(ACTION_PLAYER_UP);
    actionMap->addInputKeyToAction(ACTION_PLAYER_UP, InputKey::Key_W);
    actionMap->addAction(ACTION_PLAYER_DOWN);
    actionMap->addInputKeyToAction(ACTION_PLAYER_DOWN, InputKey::Key_S);
    actionMap->addAction(ACTION_PLAYER_SHOOT);
    actionMap->addInputKeyToAction(ACTION_PLAYER_SHOOT, InputKey::Mouse_Left);
    actionMap->addAction(ACTION_PLAYER_RELOAD);
    actionMap->addInputKeyToAction(ACTION_PLAYER_RELOAD, InputKey::Key_R);

    //Set up recording controls
    actionMap->addAction("startRecordingReplay");
    actionMap->addInputKeyToAction("startRecordingReplay", InputKey::Key_I);
    actionMap->addAction("stopRecordingReplay");
    actionMap->addInputKeyToAction("stopRecordingReplay", InputKey::Key_O);
    actionMap->addAction("playReplay");
    actionMap->addInputKeyToAction("playReplay", InputKey::Key_P);

    // GameManager Actions
    actionMap->addAction(ACTION_GAME_MANAGER_RESTART);
    actionMap->addInputKeyToAction(ACTION_GAME_MANAGER_RESTART, InputKey::Key_Backspace);
    actionMap->addAction(ACTION_GAME_MANAGER_EXIT);
    actionMap->addInputKeyToAction(ACTION_GAME_MANAGER_EXIT, InputKey::Key_Escape);
    actionMap->addAction(ACTION_GAME_MANAGER_NEXT);
    actionMap->addInputKeyToAction(ACTION_GAME_MANAGER_NEXT, InputKey::Key_Space);
    actionMap->addAction(ACTION_GAME_MANAGER_TIME_SCALE_UP);
    actionMap->addInputKeyToAction(ACTION_GAME_MANAGER_TIME_SCALE_UP, InputKey::Key_PageUp);
    actionMap->addAction(ACTION_GAME_MANAGER_TIME_SCALE_DOWN);
    actionMap->addInputKeyToAction(ACTION_GAME_MANAGER_TIME_SCALE_DOWN, InputKey::Key_PageDown);
    actionMap->addAction(ACTION_GAME_MANAGER_TIME_SCALE_RESET);
    actionMap->addInputKeyToAction(ACTION_GAME_MANAGER_TIME_SCALE_RESET, InputKey::Key_Home);

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

    //Game-based debug settings
    GolfEngine::Core::getProjectSettings().setBool(GAME_SETTINGS_DEBUG_PRINT_PLAYER_POS, false); //Output player position in console

    //Scene initialization
    auto& sceneManager = GolfEngine::Core::SceneManager::GetSceneManager();
    sceneManager.addSceneFactory<PlayerTestScene>("playerTest");
    sceneManager.addSceneFactory<SaveGameTestScene>("saveGameTest");
    sceneManager.addSceneFactory<Level1Scene>("level1");
    sceneManager.addSceneFactory<Level2Scene>("level2");
    sceneManager.addSceneFactory<Level3Scene>("level3");
    sceneManager.addSceneFactory<YouWonScene>("youWonScene");
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