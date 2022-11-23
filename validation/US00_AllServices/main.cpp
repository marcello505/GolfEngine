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

    ActionMap::getActionMap()->addAction("Reload");
    ActionMap::getActionMap()->addInputKeyToAction("Reload", Key_R);

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");


    //gets all services
    auto rs = GolfEngine::Services::Render::getService();
    auto ps = GolfEngine::Services::Physics::getService();
    auto as = GolfEngine::Services::Audio::getService();
    auto is = GolfEngine::Services::Input::getService();

    ps->setGravity(Vector2(0,5));

    as->preloadAudio(mgsThemePath);
    as->playOnChannel(0, mgsThemePath, 30);



    gameLoop.start();

    return 0;

}