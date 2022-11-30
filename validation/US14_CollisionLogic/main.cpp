//
// Created by conner on 11/29/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/BehaviourScript.h"
#include "Services/Box2DPhysicsService.h"

class PlayerScript : public BehaviourScript{
    void onCollisionEnter(RigidBody &other) override{
        _gameObject->get().getComponent<BoxCollider>().setColor(Color{255,0,0,255});
    }
};

class SceneFactory : public ISceneFactory{
    void build(Scene &scene) const override{
        auto& groundObject = scene.createNewGameObject<GameObject>();
        groundObject.addComponent<BoxCollider>(Vector2{300.0f, 20.0f});
        groundObject.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
        groundObject.setLocalPosition({320, 450});

        auto& blockObject = scene.createNewGameObject<GameObject>();
        blockObject.addComponent<BoxCollider>(Vector2{20.0f, 20.0f});
        blockObject.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        blockObject.addComponent<PlayerScript>();
        blockObject.setLocalPosition({300, 150});
    }
};

int main(int argc, char* argv[]){
    auto* physicsService = new GolfEngine::Services::Physics::Box2DPhysicsService{};
    physicsService->setGravity({0, 5.0f});
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    gameLoop.setPhysicsService(physicsService);

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();

    return 0;
}