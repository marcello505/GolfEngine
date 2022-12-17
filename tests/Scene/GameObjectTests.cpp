//
// Created by conner on 11/14/2022.
//

#include <../doctest/doctest.h>
#include "Core/SceneManager.h"
#include "Scene/Components/BehaviourScript.h"

namespace GameObjectTests{
    class DummyScript : public BehaviourScript{
    public:
        void onStart() override {}
        void reloadScene(){
            GolfEngine::SceneManager::GetSceneManager().loadScene();
        }
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

TEST_CASE("Getting a component"){
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    GolfEngine::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    // Assert
    CHECK_NOTHROW(currentScene.getRootGameObject().childAt(0).getComponent<GameObjectTests::DummyScript>());
}

TEST_CASE("Adding a component"){
    // Arrange
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();
    auto& go = currentScene.getRootGameObject();

    // Act
    go.addComponent<GameObjectTests::DummyScript>();

    // Assert
    CHECK_NOTHROW(go.getComponent<GameObjectTests::DummyScript>());
}

TEST_CASE("Removing a component"){
    // Arrange
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();
    auto& go = currentScene.getRootGameObject().childAt(0);

    // Act
    go.removeComponent<GameObjectTests::DummyScript>();

    // Assert
    CHECK_THROWS(go.getComponent<GameObjectTests::DummyScript>());
}

TEST_CASE("Reloading a scene using a custom behaviour script"){
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    GolfEngine::SceneManager::GetSceneManager().updateSceneManager();
    auto& prevCurrentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    auto& script = prevCurrentScene.getRootGameObject().childAt(0).getComponent<GameObjectTests::DummyScript>();
    script.reloadScene();
    GolfEngine::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Assert
    CHECK_NE(&currentScene, &prevCurrentScene);
}

TEST_CASE("Check if GameObject has a certain Component"){
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    GolfEngine::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    auto result = currentScene.getRootGameObject().childAt(0).hasComponent<GameObjectTests::DummyScript>();

    // Assert
    CHECK_EQ(result, true);
}

TEST_CASE("Getting list of BehaviourScript components"){
    // Arrange
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    GolfEngine::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    auto list = currentScene.getRootGameObject().childAt(0).getComponents<BehaviourScript>();

    // Assert
    CHECK_EQ(list.size(), 1);
}