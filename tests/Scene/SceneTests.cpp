//
// Created by lucas on 7-11-2022.
//

#include <../doctest/doctest.h>
#include "Core/SceneManager.h"
#include "Scene/Components/BehaviourScript.h"


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
        void build(Scene& scene) const override{
            auto& go = scene.createNewGameObject<PlayerDummy>();
        }
    };
}

TEST_CASE("Loading a scene"){
    // Arrange
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneTests::MainSceneFactory>("main");
    auto& prevScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    GolfEngine::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Assert
    CHECK_NE(&currentScene, &prevScene);
}

TEST_CASE("Reloading/Resetting a scene"){
    // Arrange
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<SceneTests::MainSceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    auto& prevScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();


    // Act
    GolfEngine::SceneManager::GetSceneManager().loadScene();
    GolfEngine::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Assert
    CHECK_NE(&currentScene, &prevScene);
}
