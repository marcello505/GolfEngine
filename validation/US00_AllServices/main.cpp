#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Services/Singletons/InputSingleton.h"
#include "Services/SDLInputService.h"
#include "Scene/Components/BoxCollider.h"
#include "SceneFactory.h"

using namespace GolfEngine::Scene;
using namespace GolfEngine::Core;

const std::string mgsThemePath = "res/mgs-theme.mp3";

int main(int argc, char* argv[]){

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

    SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    SceneManager::GetSceneManager().loadScene("main");

    //gets AudioService services
    auto as = GolfEngine::Services::Audio::getService();

    as->init();
    as->playMusic(mgsThemePath, 1.0f, false);

    gameLoop.start();

    return 0;

}