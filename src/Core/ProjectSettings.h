//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_PROJECTSETTINGS_H
#define SPC_PROJECT_PROJECTSETTINGS_H

#include <string>
#include <map>

#define SETTINGS_KEY_PARAMETER const std::string&

namespace GolfEngine::Core{
    enum class ProjectSettingsTypes{
        String,
        Integer,
        Float,
        Boolean,
        Null
    };

    /// The ProjectSettings class is a singleton that contains any settings for
    /// the current game. Unlike GameObjects, this data persists in-between scenes.
    /// Every setter will overwrite the previously set value, even if the type is different.
    class ProjectSettings {
    public:
        //Singleton method
        static ProjectSettings& getInstance(){
            static ProjectSettings settings {};
            return settings;
        }

        //Deleted methods
        ProjectSettings(ProjectSettings const&) = delete;
        void operator=(ProjectSettings const&) = delete;

        //Setters
        void setInteger(SETTINGS_KEY_PARAMETER key, int value);
        void setString(SETTINGS_KEY_PARAMETER key, const std::string& value);
        void setFloat(SETTINGS_KEY_PARAMETER key, float value);
        void setBool(SETTINGS_KEY_PARAMETER key, bool value);
        void eraseKey(SETTINGS_KEY_PARAMETER key);

        //Getters
        [[nodiscard]] ProjectSettingsTypes getType(SETTINGS_KEY_PARAMETER key) const;
        [[nodiscard]] const std::string& getString(SETTINGS_KEY_PARAMETER key) const;
        [[nodiscard]] int getInteger(SETTINGS_KEY_PARAMETER key) const;
        [[nodiscard]] float getFloat(SETTINGS_KEY_PARAMETER key) const;
        [[nodiscard]] bool getBool(SETTINGS_KEY_PARAMETER key) const;

        //Has Methods
        [[nodiscard]] bool hasString(SETTINGS_KEY_PARAMETER key) const;
        [[nodiscard]] bool hasInteger(SETTINGS_KEY_PARAMETER key) const;
        [[nodiscard]] bool hasFloat(SETTINGS_KEY_PARAMETER key) const;
        [[nodiscard]] bool hasBool(SETTINGS_KEY_PARAMETER key) const;

        //Serializing methods
        std::string toJson() const;
        void fromJson(const std::string& json) const;
    private:
        ProjectSettings() = default;

        std::map<std::string, std::string> _strings {};
        std::map<std::string, int> _integers {};
        std::map<std::string, float> _floats {};
        std::map<std::string, bool> _bools {};
    };

}



#endif //SPC_PROJECT_PROJECTSETTINGS_H
