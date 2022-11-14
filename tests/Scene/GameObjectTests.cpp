//
// Created by conner on 11/14/2022.
//

#include <../doctest/doctest.h>
#include "Scene/Scene.h"
#include "Scene/Components/BehaviourScript.h"

TEST_CASE("Component creation on GameObject"){
    // Arrange
    Scene scene{};
    GameObject go{&scene};

    // Act
    go.addComponent<BehaviourScript>();

    // Assert
    auto script {go.getComponent<BehaviourScript>()};
    CHECK_NE(script, nullptr);
}

TEST_CASE("Component removal on GameObject"){
    // Arrange
    Scene scene{};
    GameObject go{&scene};

    // Act
    go.addComponent<BehaviourScript>();
    go.removeComponent(*go.getComponent<BehaviourScript>());

    // Assert
    CHECK_EQ(go.getComponent<BehaviourScript>(), nullptr);
}