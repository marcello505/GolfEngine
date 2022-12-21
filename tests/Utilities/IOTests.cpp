#include <doctest.h>
#include <fstream>

#include "Utilities/IO.h"

using GolfEngine::Utilities::IO;

TEST_SUITE("IO"){
    TEST_CASE("deleteResourceFile() deletes a file that was just created"){
        //Arrange
        auto path = GolfEngine::Utilities::IO::resourcePath("test.txt");
        std::ofstream fileStream {path};

        //Act
        fileStream << "Hello World!" << std::endl;
        fileStream.close();

        //Assert
        CHECK(IO::resourceFileExists(path.string()));
        IO::deleteResourceFile(path.string());
        CHECK_FALSE(IO::resourceFileExists(path.string()));
    }

    TEST_CASE("deleteUserDataFile() deletes a file that was just created"){
        //Arrange
        auto path = GolfEngine::Utilities::IO::userDataPath("test.txt");
        std::ofstream fileStream {path};

        //Act
        fileStream << "Hello World!" << std::endl;
        fileStream.close();

        //Assert
        CHECK(IO::userDataFileExists(path.string()));
        IO::deleteUserDataFile(path.string());
        CHECK_FALSE(IO::userDataFileExists(path.string()));
    }

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