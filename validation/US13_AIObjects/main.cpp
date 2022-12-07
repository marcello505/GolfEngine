#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>
#include "Scene/GameObjects/UIObject/Text.h"
#include "SceneFactory.h"
#include "Services/Singletons/PathfindingSingleton.h"

#include <utility>
#include <map>


int main(int argc, char* argv[])
{
    //initialize gameloop and renderservice
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    RenderService* rs = GolfEngine::Services::Render::getService();



    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    //start gameloop
    gameLoop.start();

    return 0;
}
