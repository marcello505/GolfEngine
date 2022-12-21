//
// Created by lucas on 7-11-2022.
//

#include <../doctest/doctest.h>
#include "Core/SceneManager.h"
#include "Scene/Components/BehaviourScript.h"

using namespace GolfEngine;
using namespace GolfEngine::Scene;
using namespace GolfEngine::Scene::Components;

namespace SceneTests{
    class DummyScript : public BehaviourScript{
    private:
        int count = 0;
    public:
        void onStart() override{
            count = 1;
        }
        [[nodiscard]] int getCount() const {return count;}
    };

    class PlayerDummy : public GameObject{
    public:
        explicit PlayerDummy(const char* name = nullptr, const char* tag = nullptr)
        : GameObject(name, tag) {
            auto& c = addComponent<DummyScript>();
        }
    };

    class MainSceneFactory : public ISceneFactory{
        void build(GolfEngine::Scene::Scene& scene) const override{
            auto& go = scene.createNewGameObject<PlayerDummy>();
        }
    };
}

TEST_CASE("Loading a scene"){
    // Arrange
    Core::SceneManager::GetSceneManager().addSceneFactory<SceneTests::MainSceneFactory>("main");
    auto& prevScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    Core::SceneManager::GetSceneManager().loadScene("main");
    Core::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Assert
    CHECK_NE(&currentScene, &prevScene);
}

TEST_CASE("Reloading/Resetting a scene"){
    // Arrange
    Core::SceneManager::GetSceneManager().addSceneFactory<SceneTests::MainSceneFactory>("main");
    Core::SceneManager::GetSceneManager().loadScene("main");
    auto& prevScene = Core::SceneManager::GetSceneManager().getCurrentScene();


    // Act
    Core::SceneManager::GetSceneManager().loadScene();
    Core::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Assert
    CHECK_NE(&currentScene, &prevScene);
}
