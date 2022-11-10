//
// Created by lucas on 7-11-2022.
//

#include <doctest.h>
#include "core/SceneManager.h"

TEST_CASE("SceneManger is able to add Scene"){
    //Arrange
    SceneManager sceneManager = SceneManager();

    //Act
    sceneManager.addScene(Scene());

    //Assert
    CHECK_EQ(1,sceneManager.getScenes().size());
}
TEST_CASE("SceneManger is able to add Scene"){
    //Arrange
    SceneManager sceneManager = SceneManager();
    Scene scene =Scene();
    GameObject go = GameObject();
    go.name = "test";
    scene.setRootGameObject(go);

    //Act
    sceneManager.changeScene(scene);

    //Assert
    CHECK_EQ("test", sceneManager.getCurrentScene().getRootGameObject().name);
}


TEST_CASE("Scene is able to change root"){
    //Arrange
    Scene scene =Scene();
   GameObject go = GameObject();
   go.name = "test";
   go.tag = "testTag";
   //Act
   scene.setRootGameObject(go);

   //Assert
    CHECK_EQ(scene.getRootGameObject().name, "test");
    CHECK_EQ(scene.getRootGameObject().tag, "testTag");


}
