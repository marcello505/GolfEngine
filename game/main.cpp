
// Engine includes
#include "Core/GameLoop.h"
#include "Services/Singletons/RenderSingleton.h"

//TODO find something to fix this
#include <SDL.h>

// Game includes
#include "scenes/PlayerTestScene.h"
#include "scenes/Level2Scene.h"
#include "scenes/Level1Scene.h"


int main(int argc, char* argv[]){
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();

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

    //Set up recording controls
    actionMap->addAction("startRecordingReplay");
    actionMap->addInputKeyToAction("startRecordingReplay", InputKey::Key_I);
    actionMap->addAction("stopRecordingReplay");
    actionMap->addInputKeyToAction("stopRecordingReplay", InputKey::Key_O);
    actionMap->addAction("playReplay");
    actionMap->addInputKeyToAction("playReplay", InputKey::Key_P);

    //Scene initialization
    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    sceneManager.addScene<PlayerTestScene>("playerTest");
    sceneManager.addScene<Level1Scene>("level1");
    sceneManager.addScene<Level2Scene>("level2");
    sceneManager.loadScene("level1");

    //Render initialization
    GolfEngine::Services::Render::getService()->setScreenSize(1920, 1080);

    gameLoop.start();
    return 0;
}