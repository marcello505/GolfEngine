
// Engine includes
#include "Core/GameLoop.h"
#include "Core/Settings.h"
#include "Services/Singletons/RenderSingleton.h"
#include <SDL.h>

//TODO find something to fix this
#include <SDL.h>

// Game includes
#include "scenes/PlayerTestScene.h"
#include "scenes/SaveGameTestScene.h"


int main(int argc, char* argv[]){
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    GolfEngine::Services::Render::getService()->setWindowTitle("Game name");

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

    // Save Game actions
    actionMap->addAction("saveGame");
    actionMap->addInputKeyToAction("saveGame", InputKey::Key_K);
    actionMap->addAction("loadGame");
    actionMap->addInputKeyToAction("loadGame", InputKey::Key_L);

    //Debug settings
    GolfEngine::Core::getProjectSettings().setBool(PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS, true); //Render colliders

    //Scene initialization
    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    sceneManager.addScene<PlayerTestScene>("playerTest");
    sceneManager.addScene<SaveGameTestScene>("saveGameTest");
    sceneManager.loadScene("playerTest");

    //Render initialization
    GolfEngine::Services::Render::getService()->setScreenSize(1280, 720);

    gameLoop.start();
    return 0;
}