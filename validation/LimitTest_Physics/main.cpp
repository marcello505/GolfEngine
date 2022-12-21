//
// Created by conner on 12/21/2022.
//

#include <SDL.h>
#include <Core/GameLoop.h>
#include <Services/Singletons/PhysicsSingleton.h>
#include <Services/Singletons/RenderSingleton.h>
#include "Scene/Components/BoxCollider.h"
#include "Core/Settings.h"
#include "Scene/Components/BehaviourScript.h"
#include "Scene/Components/CircleCollider.h"

using namespace GolfEngine::Core;
using namespace GolfEngine::Scene;
using namespace GolfEngine::Input;
using namespace GolfEngine::Scene::Components;

class BallScript : public BehaviourScript{
    void onStart() override{
        auto& rb = _gameObject->get().getComponent<RigidBody>();
        rb.applyWorldForceToCenter(Vector2{110.f, 0.f});
    }
};

class InputScript : public BehaviourScript{
    void onUpdate() override{
        if(ActionMap::getActionMap()->isJustPressed("reset"))
            SceneManager::GetSceneManager().loadScene("main");
    }
};

class SceneFactory : public ISceneFactory{
    void build(GolfEngine::Scene::Scene &scene) const override{

        // Create floor
        auto& floor = scene.createNewGameObject<GameObject>();
        floor.addComponent<BoxCollider>(Vector2{600.0f, 20.0f});
        floor.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
        floor.setLocalPosition({600.f, 600.f});

        // Create 484 small boxes
        RigidBodyDef boxRBDef;
        boxRBDef.density = 0.1f;
        boxRBDef.linearDamping = 1.f;
        float xOffset = 600.f, yOffset = 330.f;
        for(int r = 0; r < 22; r++){
            for(int c = 0; c < 22; c++){
                auto& box = scene.createNewGameObject<GameObject>();
                box.addComponent<RigidBody>(boxRBDef);
                box.addComponent<BoxCollider>(Vector2{5.f, 5.f});
                box.setLocalPosition(Vector2{xOffset + (c * 11.5f), yOffset + (r * 11.5f)});
            }
        }

        // Create ball object
        auto& ball = scene.createNewGameObject<GameObject>();
        ball.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        ball.addComponent<CircleCollider>(20.f);
        ball.addComponent<BallScript>();
        ball.setLocalPosition(Vector2{-100.f, 400.f});

        auto& gm = scene.createNewGameObject<GameObject>();
        gm.addComponent<InputScript>();
    }
};

int main(int argc, char* argv[]){
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    GolfEngine::Services::Physics::getService()->setGravity({0.f, 3.f});
    GolfEngine::Services::Render::getService()->setScreenSize(1280, 720);

    ActionMap::getActionMap()->addAction("reset");
    ActionMap::getActionMap()->addInputKeyToAction("reset", Key_Space);

    getProjectSettings().setBool(PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS, true); //Render colliders

    SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();
    return 0;
}
