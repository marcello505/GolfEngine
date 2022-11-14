//
// Created by lucas on 7-11-2022.
//

#include <../doctest/doctest.h>
#include "Core/SceneManager.h"

TEST_CASE("SceneManger is able to add Scene"){
    //Arrange
    SceneManager sceneManager = SceneManager();

    //Act
    sceneManager.addScene(Scene());

    //Assert
    CHECK_EQ(1,sceneManager.getScenes().size());
}

TEST_CASE("SceneManger is able to change Scene"){
    //Arrange
    SceneManager sceneManager = SceneManager();
    Scene scene = Scene();
    sceneManager.addScene(scene);
    GameObject go = GameObject(&scene);
    go.name = "test";
    scene.setRootGameObject(&go);

    //Act
    sceneManager.changeScene(scene);

    //Assert
    CHECK_EQ("test", sceneManager.getCurrentScene().getRootGameObject()->name);
}

TEST_CASE("SceneManger is able to delete Scene"){
    //Arrange
    SceneManager sceneManager = SceneManager();
    sceneManager.addScene(Scene{});
    int beginSize = sceneManager.getScenes().size();
    //Act
    auto scenes = sceneManager.getScenes();
    auto it = scenes.begin();
    sceneManager.deleteScene(it);

    //Assert
    CHECK_EQ(0,sceneManager.getScenes().size());
    CHECK_EQ(1,beginSize);
}


TEST_CASE("Scene is able to change root"){
    //Arrange
    Scene scene = Scene();
   GameObject go = GameObject(&scene);
   go.name = "test";
   go.tag = "testTag";
   //Act
   scene.setRootGameObject(&go);

   //Assert
    CHECK_EQ(scene.getRootGameObject()->name, "test");
    CHECK_EQ(scene.getRootGameObject()->tag, "testTag");
}
