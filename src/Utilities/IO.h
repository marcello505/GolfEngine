//
// Created by marcello on 12/12/22.
//

#ifndef GOLFENGINE_IO_H
#define GOLFENGINE_IO_H

#include <filesystem>
#include <string>

namespace GolfEngine::Utilities {

    class IO {
    public:
        //Resource Folder files
        static bool resourceFileExists(const std::string& pathString);

    private:
        static std::filesystem::path convertStringToPath(const std::string& pathString);
        static std::filesystem::path getResoucesFolder();

    };
} // Utilities

#endif //GOLFENGINE_IO_H
