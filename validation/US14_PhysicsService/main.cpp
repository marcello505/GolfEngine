#include <Core/GameLoop.h>
#include <Services/Box2DPhysicsService.h>
#include <Services/SDLRenderService.h>
#include "Services/SDLInputService.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/CircleCollider.h"

GameObject* createObjects(Scene* scene){
    auto* root = new GameObject{scene};

    //Ground
    {
        auto* groundObject = new GameObject{scene, root};
        groundObject->addComponent<BoxCollider>(Vector2{300.0f, 20.0f});
        groundObject->addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
        groundObject->setLocalPosition({320, 450});
    }

    auto createBlock = [scene, root](const Vector2& pos){
        auto* blockObject = new GameObject{scene, root};
        blockObject->addComponent<BoxCollider>(Vector2{20.0f, 20.0f});
        blockObject->addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        blockObject->setLocalPosition(pos);
    };

    auto createCircle = [scene, root](const Vector2& pos){
        auto* circleObject = new GameObject{scene, root};
        circleObject->addComponent<CircleCollider>(20.f);
        circleObject->addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        circleObject->setLocalPosition(pos);
    };

    createBlock({300, 150});
    createBlock({320, 200});
    createBlock({340, 100});
    createBlock({312, 50});
    createCircle({300, 0});

    return root;
}

int main(int argc, char* argv[]){
    auto* physicsService = new GolfEngine::Services::Physics::Box2DPhysicsService{};
    physicsService->setGravity({0, 5.0f});
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    gameLoop.setPhysicsService(physicsService);
    gameLoop.setAudioService(nullptr); // Don't need audio for this test



    auto* scene = new Scene{};
    auto* root = createObjects(scene);
    root->onStart();
    gameLoop.start();

    return 0;

}