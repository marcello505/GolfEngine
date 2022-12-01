#include <Core/GameLoop.h>
#include "UIScene.h"
#include <Services/SDLRenderService.h>

int main(int argc, char* argv[])
{
    //initialize gameloop
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();

    //setup left mouse action
    ActionMap::getActionMap()->addAction("ClickButton");
    ActionMap::getActionMap()->addInputKeyToAction("ClickButton", Mouse_Left);

    //setup scene
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<UIScene>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    //start gameloop
    gameLoop.start();

    return 0;
}
