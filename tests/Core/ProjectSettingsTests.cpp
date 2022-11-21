#include <doctest.h>

#include "Core/ProjectSettings.h"

TEST_SUITE("ProjectSettings"){
    TEST_CASE("Can set and retrieve a string"){
        //Arrange
        GolfEngine::Core::ProjectSettings projectSettings {};

        //Act
        projectSettings.setSettings("test", "true");

        //Assert
        CHECK(projectSettings.hasSetting("test"));
        CHECK_EQ(projectSettings.getSetting("test"), "true");
    }

    TEST_CASE("Returns an empty string when using an invalid key"){
        //Arrange
        GolfEngine::Core::ProjectSettings projectSettings {};

        //Assert
        CHECK_FALSE(projectSettings.hasSetting("test"));
        CHECK_EQ(projectSettings.getSetting("test"), "");
    }

    TEST_CASE("Doesn't add anything on an empty key"){
        //Arrange
        GolfEngine::Core::ProjectSettings projectSettings {};

        //Act
        projectSettings.setSettings("", "test");

        //Assert
        CHECK_FALSE(projectSettings.hasSetting(""));
    }
}

