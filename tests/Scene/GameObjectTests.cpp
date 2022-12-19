//
// Created by conner on 11/14/2022.
//

#include <../doctest/doctest.h>
#include "Core/SceneManager.h"
#include "Scene/Components/BehaviourScript.h"

using namespace GolfEngine;
using namespace GolfEngine::Scene;
using namespace GolfEngine::Scene::Components;

namespace GameObjectTests{
    class DummyScript : public BehaviourScript{
    public:
        void onStart() override {}
        void reloadScene(){
            Core::SceneManager::GetSceneManager().loadScene();
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
        void build(GolfEngine::Scene::Scene& scene) const override{
            auto& go = scene.createNewGameObject<PlayerDummy>();
        }
    };

}

TEST_CASE("Getting a component"){
    Core::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    Core::SceneManager::GetSceneManager().loadScene("main");
    Core::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    // Assert
    CHECK_NOTHROW(currentScene.getRootGameObject().childAt(0).getComponent<GameObjectTests::DummyScript>());
}

TEST_CASE("Adding a component"){
    // Arrange
    Core::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    Core::SceneManager::GetSceneManager().loadScene("main");
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();
    auto& go = currentScene.getRootGameObject();

    // Act
    go.addComponent<GameObjectTests::DummyScript>();

    // Assert
    CHECK_NOTHROW(go.getComponent<GameObjectTests::DummyScript>());
}

TEST_CASE("Removing a component"){
    // Arrange
    Core::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    Core::SceneManager::GetSceneManager().loadScene("main");
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();
    auto& go = currentScene.getRootGameObject().childAt(0);

    // Act
    go.removeComponent<GameObjectTests::DummyScript>();

    // Assert
    CHECK_THROWS(go.getComponent<GameObjectTests::DummyScript>());
}

TEST_CASE("Reloading a scene using a custom behaviour script"){
    Core::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    Core::SceneManager::GetSceneManager().loadScene("main");
    Core::SceneManager::GetSceneManager().updateSceneManager();
    auto& prevCurrentScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    auto& script = prevCurrentScene.getRootGameObject().childAt(0).getComponent<GameObjectTests::DummyScript>();
    script.reloadScene();
    Core::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Assert
    CHECK_NE(&currentScene, &prevCurrentScene);
}

TEST_CASE("Check if GameObject has a certain Component"){
    Core::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    Core::SceneManager::GetSceneManager().loadScene("main");
    Core::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    auto result = currentScene.getRootGameObject().childAt(0).hasComponent<GameObjectTests::DummyScript>();

    // Assert
    CHECK_EQ(result, true);
}

TEST_CASE("Getting list of BehaviourScript components"){
    // Arrange
    Core::SceneManager::GetSceneManager().addSceneFactory<GameObjectTests::MainSceneFactory>("main");
    Core::SceneManager::GetSceneManager().loadScene("main");
    Core::SceneManager::GetSceneManager().updateSceneManager();
    auto& currentScene = Core::SceneManager::GetSceneManager().getCurrentScene();

    // Act
    auto list = currentScene.getRootGameObject().childAt(0).getComponents<BehaviourScript>();

    // Assert
    CHECK_EQ(list.size(), 1);
}