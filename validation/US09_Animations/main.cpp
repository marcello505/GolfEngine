//
// Created by conner on 11/23/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "SceneFactory.h"

int main(int argc, char* argv[]){
    GameLoop gameLoop{};
    gameLoop.useDefaultServices();

    ActionMap::getActionMap()->addAction("test");
    ActionMap::getActionMap()->addInputKeyToAction("test", Key_T);

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();
    return 0;
}