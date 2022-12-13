//
// Created by marcello on 12/12/22.
//

#include <algorithm>
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

    std::filesystem::path IO::_convertStringToPath(const std::string& pathString) {
        std::string result {pathString};

        std::replace(result.begin(), result.end(), '\\', '/');
        return std::filesystem::path{result};
    }



} // Utilities
