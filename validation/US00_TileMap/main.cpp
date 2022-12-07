//
// Created by conner on 12/5/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "Scene/Components/TiledComponent.h"
#include "Scene/Components/BehaviourScript.h"

class MoveScript : public BehaviourScript {
public:
    void onUpdate() override{
        if(ActionMap::getActionMap()->isPressed("left")){
            auto transform = _gameObject->get().getLocalTransform();
            transform.position.x += 2;
            _gameObject->get().setLocalTransform(transform);
        }
        if(ActionMap::getActionMap()->isPressed("right")){
            auto transform = _gameObject->get().getLocalTransform();
            transform.position.x -= 2;
            _gameObject->get().setLocalTransform(transform);
        }
        if(ActionMap::getActionMap()->isPressed("up")){
            auto transform = _gameObject->get().getLocalTransform();
            transform.position.y += 2;
            _gameObject->get().setLocalTransform(transform);
        }
        if(ActionMap::getActionMap()->isPressed("down")){
            auto transform = _gameObject->get().getLocalTransform();
            transform.position.y -= 2;
            _gameObject->get().setLocalTransform(transform);
        }
    }
};

class SceneFactory : public ISceneFactory {
    void build(Scene& scene) const override{
        auto& go = scene.createNewGameObject<GameObject>();
        go.addComponent<TiledComponent>(R"(..\..\..\validation\US00_TileMap\res\map.tmx)", R"(..\..\..\validation\US00_TileMap\res\Hotline-Miami-TileSet.tsx)", Vector2(4,4));
        go.addComponent<MoveScript>();
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