//
// Created by conner on 11/23/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "SceneFactory.h"
#include "Services/Singletons/PhysicsSingleton.h"

int main(int argc, char* argv[]){
    GameLoop gameLoop{};
    gameLoop.useDefaultServices();

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    ActionMap::getActionMap()->addAction("Stop");
    ActionMap::getActionMap()->addInputKeyToAction("Stop", Key_Space);

    ActionMap::getActionMap()->addAction("Start");
    ActionMap::getActionMap()->addInputKeyToAction("Start", Key_P);

    auto x  = GolfEngine::Services::Physics::getService();
    x->setGravity(Vector2(0,0.3f));

    gameLoop.start();
    return 0;
}