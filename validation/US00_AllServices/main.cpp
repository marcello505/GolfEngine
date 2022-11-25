#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Services/Singletons/InputSingleton.h"
#include "Services/SDLInputService.h"
#include "Scene/Components/BoxCollider.h"
#include "SceneFactory.h"

/*TODO
 * 1. Make getters/setters for actionMap so you dont always need to create new actionmap, but can just use predefined actionmap from engine
 *
 *
 */


const std::string mgsThemePath = R"(..\..\..\validation\US00_AllServices\res\mgs-theme.mp3)";


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


    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");


    //gets AudioService services
    auto as = GolfEngine::Services::Audio::getService();


    as->preloadAudio(mgsThemePath);
    as->setVolumeChannel(0,100);
    as->playOnChannel(0, mgsThemePath, 5);



    gameLoop.start();

    return 0;

}