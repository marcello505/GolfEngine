#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Services/Singletons/InputSingleton.h"
#include "Services/SDLInputService.h"
#include "Scene/Components/BoxCollider.h"
#include "SpriteDrawable.h"
#include "Scene/Components/Sprite.h"

/*TODO
 * 1. Make getters/setters for actionMap so you dont always need to create new actionmap, but can just use predefined actionmap from engine
 *
 *
 */


const std::string mgsThemePath = R"(..\..\..\validation\US00_AllServices\res\mgs-theme.mp3)";

GameObject* createObjects(Scene* scene){
    auto* root = new GameObject{scene};

    //Ground
    {
        auto* groundObject = new GameObject{scene, root};
        groundObject->addComponent<BoxCollider>(Vector2{300.0f, 20.0f});
        groundObject->addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
        groundObject->setLocalPosition({320, 450});
    }

    //Ground
    {
        auto* groundObject = new GameObject{scene, root};
        groundObject->addComponent<BoxCollider>(Vector2{20.0f, 20.0f});
        groundObject->addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        groundObject->setLocalPosition({300, 150});
    }

    return root;
}



int main(int argc, char* argv[]){
    std::unique_ptr<ActionMap> _actionMap = std::make_unique<ActionMap>();
    _actionMap->addAction("Reload");

    // binding actions to keys
    _actionMap->addInputKeyToAction("Reload", Key_R);
    auto inputService = new SDLInputService(_actionMap.get());

    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    gameLoop.setInputService(inputService);



    //gets all services
    auto rs = GolfEngine::Services::Render::getService();
    auto ps = GolfEngine::Services::Physics::getService();
    auto as = GolfEngine::Services::Audio::getService();
    auto is = GolfEngine::Services::Input::getService();

    ps->setGravity(Vector2(0,5));

    as->preloadAudio(mgsThemePath);
    as->playOnChannel(0, mgsThemePath, 50);




    auto* scene = new Scene{};
    auto* root = createObjects(scene);
    root->onStart();

    gameLoop.start();

    return 0;

}