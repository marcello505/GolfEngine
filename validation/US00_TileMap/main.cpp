//
// Created by conner on 12/5/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "Scene/Components/TiledComponent.h"
#include "Scene/Components/BehaviourScript.h"
#include "Scene/Components/BoxCollider.h"

class MoveScript : public BehaviourScript {
public:
    void onUpdate() override{
        if(ActionMap::getActionMap()->isPressed("left")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{-0.2f, 0});
        }
        if(ActionMap::getActionMap()->isPressed("right")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{0.2f, 0});
        }
        if(ActionMap::getActionMap()->isPressed("up")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{0, -0.2f});
        }
        if(ActionMap::getActionMap()->isPressed("down")){
            _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2{0, 0.2f});
        }
    }
};

class SceneFactory : public ISceneFactory {
    void build(Scene& scene) const override{
        auto& map = scene.createNewGameObject<GameObject>();
        auto& mapComp = map.addComponent<TiledComponent>(R"(..\..\..\validation\US00_TileMap\res\map.tmx)", Vector2(2,2));
        mapComp.initColliders();
        auto& go = scene.createNewGameObject<GameObject>();
        go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
        go.addComponent<BoxCollider>(Vector2{10, 10});
        go.addComponent<MoveScript>();
        go.setLocalPosition(Vector2{200, 200});
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