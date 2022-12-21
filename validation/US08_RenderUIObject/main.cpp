#include <Core/GameLoop.h>
#include "UIScene.h"
#include <Services/SDLRenderService.h>

using namespace GolfEngine::Core;

int main(int argc, char* argv[])
{
    //initialize gameloop
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();

    //setup left mouse action
    ActionMap::getActionMap()->addAction("ClickButton");
    ActionMap::getActionMap()->addInputKeyToAction("ClickButton", Mouse_Left);

    //setup scene
    SceneManager::GetSceneManager().addSceneFactory<UIScene>("main");
    SceneManager::GetSceneManager().loadScene("main");

    //start gameloop
    gameLoop.start();

    return 0;
}
