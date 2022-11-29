
// Engine includes
#include "Core/GameLoop.h"
#include "Services/Singletons/RenderSingleton.h"

// Game includes
#include "scenes/PlayerTestScene.h"


int main(){
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

    //Scene initialization
    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    sceneManager.addScene<PlayerTestScene>("playerTest");
    sceneManager.loadScene("playerTest");

    //Render initialization
    GolfEngine::Services::Render::getService()->setScreenSize(1280, 720);

    gameLoop.start();
}