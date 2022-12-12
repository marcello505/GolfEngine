//
// Created by marcello on 12/12/22.
//

#include <algorithm>
#include "IO.h"

#define USER_DATA_FOLDER "userdata"
#define RESOURCES_FOLDER "res"

namespace GolfEngine::Utilities {
    bool IO::resourceFileExists(const std::string& pathString) {
        auto resFolder = getResoucesFolder();
        resFolder /= convertStringToPath(pathString);


        return std::filesystem::exists(resFolder);
    }

    std::filesystem::path IO::getResoucesFolder(){
        std::filesystem::path result {RESOURCES_FOLDER};
        if(!std::filesystem::exists(result)){
            //Create folder if it doesn't exist
            std::filesystem::create_directory(result);
        }

        return result;
    }

    std::filesystem::path IO::convertStringToPath(const std::string& pathString) {
        std::string result {pathString};

        std::replace(result.begin(), result.end(), '\\', '/');
        return std::filesystem::path{result};
    }

} // Utilities
