#include <doctest.h>

#include "Utilities/IO.h"

TEST_SUITE("IO"){
    TEST_CASE("loadSettings() correctly loads in XML saved by saveSettings()"){
        //Arrange
        GolfEngine::Core::Settings settings {};
        std::string path {"settings"};
        std::string key {"TEST"};

        settings.setBool(key, true);

        //Act
        GolfEngine::Utilities::IO::saveSettings(path, settings);
        auto loadedSettings = GolfEngine::Utilities::IO::loadSettings(path);

        //Assert
        CHECK(GolfEngine::Utilities::IO::userDataFileExists(path));
        CHECK(loadedSettings.getBool(key));
    }

    TEST_CASE("loadSettings() throws an exception when file does not exist"){
        std::string path {"DOES_NOT_EXIST"};
        CHECK_FALSE(GolfEngine::Utilities::IO::userDataFileExists(path));
        CHECK_THROWS(GolfEngine::Utilities::IO::loadSettings(path));
    }
}