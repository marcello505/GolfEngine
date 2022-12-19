//
// Created by conner on 11/23/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "SceneFactory.h"

using namespace GolfEngine::Core;

int main(int argc, char* argv[]){
    GameLoop gameLoop{};
    gameLoop.useDefaultServices();

    ActionMap::getActionMap()->addAction("test");
    ActionMap::getActionMap()->addInputKeyToAction("test", Key_T);

    SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();
    return 0;
}