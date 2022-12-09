#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>
#include "Scene/GameObjects/UIObject/Text.h"
#include "SceneFactory.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"

#include <utility>
#include <map>


int main(int argc, char* argv[])
{
    //initialize gameloop and renderservice
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();

    ActionMap::getActionMap()->addAction("Left");
    ActionMap::getActionMap()->addAction("Right");
    ActionMap::getActionMap()->addAction("Up");
    ActionMap::getActionMap()->addAction("Down");

    ActionMap::getActionMap()->addInputKeyToAction("Left", Key_Left);
    ActionMap::getActionMap()->addInputKeyToAction("Right", Key_Right);
    ActionMap::getActionMap()->addInputKeyToAction("Up", Key_Up);
    ActionMap::getActionMap()->addInputKeyToAction("Down", Key_Down);



    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    //start gameloop
    gameLoop.start();

    return 0;
}
