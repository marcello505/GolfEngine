//
// Created by conner on 12/5/2022.
//

#include "Core/GameLoop.h"
#include <SDL.h>
#include "Scene/Components/TiledComponent.h"

class SceneFactory : public ISceneFactory {
    void build(Scene& scene) const override{
        auto& go = scene.createNewGameObject<GameObject>();
        go.addComponent<TiledComponent>(R"(..\..\..\validation\US00_TileMap\res\map.tmx)", R"(..\..\..\validation\US00_TileMap\res\Hotline-Miami-TileSet.tsx)");
    }
};

int main(int argc, char* argv[]){
    GameLoop gameLoop{};
    gameLoop.useDefaultServices();

    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    gameLoop.start();
    return 0;
}