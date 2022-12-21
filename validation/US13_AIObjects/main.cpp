#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>
#include "Scene/GameObjects/UIObject/Text.h"
#include "SceneFactory.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"
#include "Core/Settings.h"

#include <utility>
#include <map>


using namespace GolfEngine::Scene;
using namespace GolfEngine::Core;

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

    GolfEngine::Core::getProjectSettings().setBool(PROJECT_SETTINGS_BOOL_RENDER_PATHFINDING, true); //Render pathfinding nodes

    //Creates margin around all recColliders
    if(GolfEngine::Services::Pathfinding::hasService())
        GolfEngine::Services::Pathfinding::getService()->setMarginAroundRectColliders(10);

    SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    SceneManager::GetSceneManager().loadScene("main");

    //start gameloop
    gameLoop.start();

    return 0;
}
