//
// Created by marcello on 12/12/22.
//

#include <algorithm>
#include <fstream>
#include "IO.h"

#define USER_DATA_FOLDER "userdata"
#define RESOURCES_FOLDER "res"

namespace GolfEngine::Utilities {
    std::filesystem::path IO::resourcePath(const std::string& relativePath) {
        return std::filesystem::absolute(_getResoucesFolder() /= _convertStringToPath(relativePath));
    }

    std::filesystem::path IO::resourcePath() {
        return std::filesystem::absolute(_getResoucesFolder());
    }

    bool IO::resourceFileExists(const std::string& relativePath) {
        auto path = resourcePath(relativePath);
        return std::filesystem::exists(path);
    }

    void IO::deleteResourceFile(const std::string& relativePath) {
        std::filesystem::remove(resourcePath(relativePath));
    }

    std::filesystem::path IO::userDataPath(const std::string& relativePath) {
        return std::filesystem::absolute(_getUserDataFolder() /= _convertStringToPath(relativePath));
    }

    std::filesystem::path IO::userDataPath() {
        return std::filesystem::absolute(_getUserDataFolder());
    }

    bool IO::userDataFileExists(const std::string& relativePath) {
        auto path = userDataPath(relativePath);
        return std::filesystem::exists(path);
    }

    void IO::saveSettings(const std::string& relativePath, const Core::Settings& projectSettings) {
        auto path = userDataPath(relativePath);

        std::ofstream file {path};

        file << projectSettings.toXml();
        file.close();
    }

    Core::Settings IO::loadSettings(const std::string& relativePath) {
        Core::Settings result {};
        auto path = userDataPath(relativePath);

        std::ifstream file {path};
        std::string line {};
        std::string fileContent {};

        if(file.is_open()){
            while(getline(file, line)){
                fileContent.append(line + '\n');
            }
        }
        else
            throw std::runtime_error("Unable to open/load file: " + path.string() + "in IO::saveSettings");

        result.fromXml(fileContent);
        return result;
    }

    //================
    //Private methods
    std::filesystem::path IO::_convertStringToPath(const std::string& pathString) {
        std::string result {pathString};

        std::replace(result.begin(), result.end(), '\\', '/');
        return std::filesystem::path{result};
    }

    std::filesystem::path IO::_getResoucesFolder(){
        std::filesystem::path result {RESOURCES_FOLDER};
        if(!std::filesystem::exists(result)){
            //Create folder if it doesn't exist
            std::filesystem::create_directory(result);
        }
        else if(!std::filesystem::is_directory(result)){
            // path is occupied by a file, not a directory
            std::string err {};
            err.append("Resource Path: \"").append(RESOURCES_FOLDER).append("\" already exists as a file.");
            throw std::runtime_error(err);
        }

        return result;
    }

    std::filesystem::path IO::_getUserDataFolder() {
        std::filesystem::path result {USER_DATA_FOLDER};
        if(!std::filesystem::exists(result)){
            //Create folder if it doesn't exist
            std::filesystem::create_directory(result);
        }
        else if(!std::filesystem::is_directory(result)){
            // path is occupied by a file, not a directory
            std::string err {};
            err.append("Resource Path: \"").append(USER_DATA_FOLDER).append("\" already exists as a file.");
            throw std::runtime_error(err);
        }

        return result;
    }



} // Utilities
