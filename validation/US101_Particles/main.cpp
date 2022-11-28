//
// Created by conner on 11/23/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "SceneFactory.h"

int main(int argc, char* argv[]){
    GameLoop gameLoop{};
    gameLoop.useDefaultServices();

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    gameLoop.setPhysicsService(nullptr);

    gameLoop.start();
    return 0;
}