//
// Created by conner on 12/8/2022.
//

#include <SDL.h>
#include "Core/GameLoop.h"
#include "Scene/Components/BehaviourScript.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/CircleCollider.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/TiledComponent.h"

using namespace GolfEngine::Scene;
using namespace GolfEngine::Core;
using namespace GolfEngine::Scene::Components;

class MoveScript : public BehaviourScript{
    Camera* cam1, *cam2;
public:
    MoveScript(Camera* c1, Camera* c2) : cam1{c1}, cam2{c2}{

    }
    void onUpdate() override{
        if(ActionMap::getActionMap()->isPressed("left")){
            _gameObject->get().getComponent<RigidBody>().applyWorldForceToCenter(Vector2{-2,0});
        }
        if(ActionMap::getActionMap()->isPressed("right")){
            _gameObject->get().getComponent<RigidBody>().applyWorldForceToCenter(Vector2{2,0});
        }
        if(ActionMap::getActionMap()->isPressed("up")){
            _gameObject->get().getComponent<RigidBody>().applyWorldForceToCenter(Vector2{0,-2});
        }
        if(ActionMap::getActionMap()->isPressed("down")){
            _gameObject->get().getComponent<RigidBody>().applyWorldForceToCenter(Vector2{0,2});
        }
        if(ActionMap::getActionMap()->isJustPressed("switchCam")){
            if(&Camera::getMainCamera()->get() == cam1)
                Camera::setMainCamera(*cam2);
            else
                Camera::setMainCamera(*cam1);
        }
    }
};

class SceneFactory : public ISceneFactory{
    void build(Scene &scene) const override{
        auto& map = scene.createNewGameObject<GameObject>();
        auto& mapComp = map.addComponent<TiledComponent>(R"(res/map.tmx)", Vector2{2,2});
        mapComp.initColliders();

        auto& go = scene.createNewGameObject<GameObject>();
        go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        go.addComponent<BoxCollider>(Vector2{12.5f, 12.5f});
        go.setLocalTransform(Transform{Vector2{50, 50}, 0, Vector2{1,1}});

//        auto& wall = scene.createNewGameObject<GameObject>();
//        wall.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
//        wall.addComponent<BoxCollider>(Vector2{300, 50});
//        wall.setLocalTransform(Transform{Vector2{200, 300}, 0, Vector2{1,1}});

        auto& sprite = scene.createNewGameObject<GameObject>();
        sprite.addComponent<SpriteComponent>("res/player.png", Vector2{2,2});
        sprite.setLocalTransform(Transform{Vector2{400, 100}, 0, Vector2{1,1}});

        auto& cam = scene.createNewGameObject<Camera>(go, 640.0f, 480.0f);

        auto& stationaryCam = scene.createNewGameObject<Camera>(640.0f, 480.0f);
        stationaryCam.addComponent<CircleCollider>(20.0f);
        stationaryCam.setLocalPosition(Vector2{300, 200});
        go.addComponent<MoveScript>(&cam, &stationaryCam);
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
    ActionMap::getActionMap()->addAction("switchCam");
    ActionMap::getActionMap()->addInputKeyToAction("switchCam", Key_Space);

    SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();
    return 0;
}