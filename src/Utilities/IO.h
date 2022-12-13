//
// Created by marcello on 12/12/22.
//

#ifndef GOLFENGINE_IO_H
#define GOLFENGINE_IO_H

#include <filesystem>
#include <string>

#include "Core/Settings.h"

namespace GolfEngine::Utilities {

    class IO {
    public:
        //Resource Folder files
        /// Get the path to the resource folder file using the relativePath
        /// \param relativePath path to the file relative to the resource folder
        /// \return Absolute path to the file
        static std::filesystem::path resourcePath(const std::string& relativePath);
        /// Get the path to the resource folder
        /// \return Absolute path to the resource folder
        static std::filesystem::path resourcePath();
        /// Check if resource file exists
        /// \param relativePath path to the file relative to the resource folder
        /// \return True if file exists, otherwise false
        static bool resourceFileExists(const std::string& relativePath);
        /// Delete the file from the resource directory
        /// \param relativePath
        static void deleteResourceFile(const std::string& relativePath);

        //Userdata Files
        /// Get the path to the user data file using the relativePath
        /// \param relativePath path to the file relative to the user data folder
        /// \return Absolute path to the file
        static std::filesystem::path userDataPath(const std::string& relativePath);
        /// Get the path to the user data folder
        /// \return Absolute path to the resource folder
        static std::filesystem::path userDataPath();
        /// Check if resource file exists
        /// \param relativePath path to the file relative to the resource folder
        /// \return True if file exists, otherwise false
        static bool userDataFileExists(const std::string& relativePath);
        static void saveProjectSettings(const std::string& relativePath, const Core::Settings& projectSettings);
        static Core::Settings loadProjectSettings(const std::string& relativePath);

    private:
        static std::filesystem::path _convertStringToPath(const std::string& pathString);
        static std::filesystem::path _getResoucesFolder();
        static std::filesystem::path _getUserDataFolder();

    };
} // Utilities

#endif //GOLFENGINE_IO_H
