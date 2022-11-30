#include <Core/GameLoop.h>
#include "SceneFactory.h"
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>


#include <iostream>


int main(int argc, char* argv[])
{
    //initialize gameloop and renderservice
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();

    ActionMap::getActionMap()->addAction("ClickButton");
    ActionMap::getActionMap()->addInputKeyToAction("ClickButton", Mouse_Left);
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    //start gameloop
    gameLoop.start();

    return 0;
}
