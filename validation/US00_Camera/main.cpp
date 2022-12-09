//
// Created by conner on 12/8/2022.
//

#include <SDL.h>
#include "Core/GameLoop.h"
#include "Scene/Components/BehaviourScript.h"
#include "Scene/Components/BoxCollider.h"

class MoveScript : public BehaviourScript{
    void onUpdate() override{
        if(ActionMap::getActionMap()->isPressed("left")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{-2,0});
        }
        if(ActionMap::getActionMap()->isPressed("right")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{2,0});
        }
        if(ActionMap::getActionMap()->isPressed("up")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{0,-2});
        }
        if(ActionMap::getActionMap()->isPressed("down")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{0,2});
        }
    }
};

class SceneFactory : public ISceneFactory{
    void build(Scene &scene) const override{
        auto& go = scene.createNewGameObject<GameObject>();
        go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        go.addComponent<BoxCollider>(Vector2{25, 25});
        go.addComponent<MoveScript>();
        go.setLocalTransform(Transform{Vector2{50, 50}, 0, Vector2{1,1}});

        auto& wall = scene.createNewGameObject<GameObject>();
        wall.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
        wall.addComponent<BoxCollider>(Vector2{300, 50});
        wall.setLocalTransform(Transform{Vector2{200, 300}, 0, Vector2{1,1}});

        auto& cam = scene.createNewGameObject<Camera>(go, 640.0f, 480.0f);
    }
};

int main(int argc, char* argv[]){
    GameLoop gameLoop{};
    gameLoop.useDefaultServices();

    ActionMap::getActionMap()->addAction("left");
    ActionMap::getActionMap()->addInputKeyToAction("left", Key_Left);
    ActionMap::getActionMap()->addAction("right");
    ActionMap::getActionMap()->addInputKeyToAction("right", Key_Right);
    ActionMap::getActionMap()->addAction("up");
    ActionMap::getActionMap()->addInputKeyToAction("up", Key_Up);
    ActionMap::getActionMap()->addAction("down");
    ActionMap::getActionMap()->addInputKeyToAction("down", Key_Down);

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();
    return 0;
}