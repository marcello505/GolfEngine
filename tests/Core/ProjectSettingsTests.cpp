#include <doctest.h>

#include "Core/ProjectSettings.h"

TEST_CASE(""){
    //Arrange
    GolfEngine::Core::ProjectSettings projectSettings {};

    //Act
    projectSettings.setSettings("test/a", "true");

    //Assert
    CHECK(projectSettings.hasSetting("test/a"));
    CHECK_EQ(projectSettings.getSetting("test/a"), "true");
}
