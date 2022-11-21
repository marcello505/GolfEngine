//
// Created by lucas on 7-11-2022.
//

#include <../doctest/doctest.h>
#include "Core/SceneManager.h"
#include "Scene/Components/BehaviourScript.h"

namespace SceneTests{
    class DummyScript : public BehaviourScript{
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
   auto* go = new GameObject{scene};
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
    auto* go1 = new GameObject{scene};
    go1->addComponent<BehaviourScript>();
    go1->addComponent<SceneTests::DummyScript>();
    auto* go2 = new GameObject{scene, go1};
    go2->addComponent<SceneTests::DummyScript>();

    // Act
    Core::SceneManager::GetSceneManager()->loadScene("main");
    auto loadedScene = Core::SceneManager::GetSceneManager()->getCurrentScene();

    // Assert
    auto* child = Core::SceneManager::GetSceneManager()->getCurrentScene()->getRootGameObject()->childAt(0)->childAt(0);
    CHECK_NE(child, nullptr);
    CHECK_NE(go2, child);
}