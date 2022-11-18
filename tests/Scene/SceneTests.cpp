//
// Created by lucas on 7-11-2022.
//

#include <../doctest/doctest.h>
#include "Core/SceneManager.h"
#include "Scene/Components/BehaviourScript.h"

namespace SceneTests{
    class DummyScript : public BehaviourScript{};

    class DummyGameManager : public BehaviourScript{
    public:
        void restartLevel(){
            Core::SceneManager::GetSceneManager()->loadScene("main");
        }
    };
}

TEST_CASE("SceneManger is able to add Scene"){
    //Arrange
    //Act
    Core::SceneManager::GetSceneManager()->createScene("main");

    //Assert
    CHECK_EQ(1,Core::SceneManager::GetSceneManager()->getScenes().size());

    // Cleanup
    Core::SceneManager::GetSceneManager()->deleteScene("main");
}

TEST_CASE("SceneManger is able to change Scene"){
    //Arrange
    auto* sm = Core::SceneManager::GetSceneManager();

    Core::SceneManager::GetSceneManager()->createScene("main");
    auto prevScene = Core::SceneManager::GetSceneManager()->getCurrentScene();

    //Act
    Core::SceneManager::GetSceneManager()->loadScene("main");
    auto currentScene = Core::SceneManager::GetSceneManager()->getCurrentScene();

    //Assert
    CHECK_NE(prevScene, currentScene);

    // Cleanup
    Core::SceneManager::GetSceneManager()->deleteScene("main");
}

TEST_CASE("SceneManger is able to delete Scene"){
    //Arrange
    Core::SceneManager::GetSceneManager()->createScene("main");
    int beginSize = Core::SceneManager::GetSceneManager()->getScenes().size();

    //Act
    Core::SceneManager::GetSceneManager()->deleteScene("main");

    //Assert
    CHECK_EQ(0,Core::SceneManager::GetSceneManager()->getScenes().size());
    CHECK_EQ(1,beginSize);

    // Cleanup
    Core::SceneManager::GetSceneManager()->deleteScene("main");
}

TEST_CASE("Scene is able to change root"){
    //Arrange
    auto* scene = new Scene();
    auto* go = new GameObject();

   go->name = "test";
   go->tag = "testTag";

   //Act
   scene->setRootGameObject(go);

   //Assert
    CHECK_EQ(scene->getRootGameObject()->name, "test");
    CHECK_EQ(scene->getRootGameObject()->tag, "testTag");

    // Cleanup
    delete scene;
}

TEST_CASE("Scene is able to load and copy more advanced Scene"){
    // Arrange
    auto* scene = Core::SceneManager::GetSceneManager()->createScene("main");
    auto* go1 = scene->createGameObject(new GameObject{});
    go1->addComponent<BehaviourScript>();
    go1->addComponent<SceneTests::DummyScript>();
    auto* go2 = scene->createGameObject(new GameObject{}, go1);
    go2->addComponent<SceneTests::DummyScript>();

    // Act
    Core::SceneManager::GetSceneManager()->loadScene("main");

    // Assert
    auto* child = Core::SceneManager::GetSceneManager()->getCurrentScene()->getRootGameObject()->childAt(0)->childAt(0);
    CHECK_NE(child, nullptr);
    CHECK_NE(go2, nullptr);
    CHECK_NE(go2, child);
}

TEST_CASE("Loading scene from a behaviour script"){
    // Arrange
    auto* scene = Core::SceneManager::GetSceneManager()->createScene("main");
    auto* go = scene->createGameObject(new GameObject{});
    go->addComponent<SceneTests::DummyGameManager>();
    Core::SceneManager::GetSceneManager()->loadScene("main");

    // Act
    Core::SceneManager::GetSceneManager()->getCurrentScene()->getRootGameObject()->tag = "newTag";
    auto* gm = go->getComponent<SceneTests::DummyGameManager>();
    gm->restartLevel();

    // Assert
    auto currentScene = Core::SceneManager::GetSceneManager()->getCurrentScene();
    // Check if changes made in scene are now reverted
    CHECK_EQ(currentScene->getRootGameObject()->tag, "default");
}