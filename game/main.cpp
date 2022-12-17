
// Engine includes
#include "Core/GameLoop.h"
#include "Core/Settings.h"
#include "Services/Singletons/RenderSingleton.h"

// Game includes
#include "scenes/PlayerTestScene.h"

#include "scenes/MainMenuScene.h"
#include "scenes/SelectLevelScene.h"
#include "scenes/SettingsScene.h"
#include "Scene/Components/AudioSource.h"

#include "scenes/SaveGameTestScene.h"
#include <SDL.h>



int main(int argc, char* argv[]){
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    GolfEngine::Services::Render::getService()->setWindowTitle("Game name");

    //Render initialization
    GolfEngine::Services::Render::getService()->setScreenSize(1920, 1080);

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
    actionMap->addAction("clickButton");
    actionMap->addInputKeyToAction("clickButton", Mouse_Left);

    //Audio initialisation
/*    GolfEngine::Scene::Components::AudioSource mgsThemeSound {static_cast<bool>(R"(../../game/res/audio/mgs-theme.flac)"), true};
    mgsThemeSound.play(true);*/

    // Save Game actions
    actionMap->addAction("saveGame");
    actionMap->addInputKeyToAction("saveGame", InputKey::Key_K);
    actionMap->addAction("loadGame");
    actionMap->addInputKeyToAction("loadGame", InputKey::Key_L);

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
    return 0;
}