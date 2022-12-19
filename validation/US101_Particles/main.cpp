//
// Created by conner on 11/23/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "SceneFactory.h"
#include "Services/Singletons/PhysicsSingleton.h"

using namespace GolfEngine::Core;

int main(int argc, char* argv[]){
    GameLoop gameLoop{};
    gameLoop.useDefaultServices();

    SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    SceneManager::GetSceneManager().loadScene("main");

    // Press Space to Stop Paritcles
    ActionMap::getActionMap()->addAction("Stop");
    ActionMap::getActionMap()->addInputKeyToAction("Stop", Key_Space);

    // Press P to start Paritcles
    ActionMap::getActionMap()->addAction("Start");
    ActionMap::getActionMap()->addInputKeyToAction("Start", Key_P);

    gameLoop.start();
    return 0;
}