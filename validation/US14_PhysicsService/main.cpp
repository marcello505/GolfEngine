#include <Core/GameLoop.h>
#include <Services/Box2DPhysicsService.h>
#include <Services/SDLRenderService.h>
#include "Services/SDLInputService.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/CircleCollider.h"

class UIScene : public ISceneFactory{
    void build(Scene &scene) const override{
        auto& groundObject = scene.createNewGameObject<GameObject>();
        groundObject.addComponent<BoxCollider>(Vector2{300.0f, 20.0f});
        groundObject.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
        groundObject.setLocalPosition({320, 450});

        auto createBlock = [&scene](const Vector2& pos){
            auto& blockObject = scene.createNewGameObject<GameObject>();
            blockObject.addComponent<BoxCollider>(Vector2{20.0f, 20.0f});
            blockObject.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
            blockObject.setLocalPosition(pos);
        };

        auto createCircle = [&scene](const Vector2& pos){
            auto& circleObject = scene.createNewGameObject<GameObject>();
            circleObject.addComponent<CircleCollider>(20.f);
            circleObject.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
            circleObject.setLocalPosition(pos);
        };

        createBlock({300, 150});
        createBlock({320, 200});
        createBlock({340, 100});
        createBlock({312, 50});
        createCircle({300, 0});
    }
};

int main(int argc, char* argv[]){
    auto* physicsService = new GolfEngine::Services::Physics::Box2DPhysicsService{};
    physicsService->setGravity({0, 5.0f});
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    gameLoop.setPhysicsService(physicsService);
    gameLoop.setAudioService(nullptr); // Don't need audio for this test

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<UIScene>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();

    return 0;

}