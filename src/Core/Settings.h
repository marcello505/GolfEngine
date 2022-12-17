//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_PROJECTSETTINGS_H
#define SPC_PROJECT_PROJECTSETTINGS_H

#include <string>
#include <map>

#define SETTINGS_KEY_PARAMETER const std::string&

//Engine recognized Project Settings keys
#define PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS "debugRenderColliders" //Enable/Disable rendering of Colliders
#define PROJECT_SETTINGS_BOOL_RENDER_PATHFINDING "debugRenderPathfinding" //Enable/Disable rendering of pathfinding nodes

namespace GolfEngine::Core{
    enum class SettingsTypes{
        String,
        Integer,
        Float,
        Boolean,
        Null
    };

    /// The Settings class is that contains any settings for the current game.
    /// Every setter will overwrite the previously set value, even if the type is different.
    class Settings {
    public:

        //Setters
        void setInteger(SETTINGS_KEY_PARAMETER key, int value);
        void setString(SETTINGS_KEY_PARAMETER key, const std::string& value);
        void setFloat(SETTINGS_KEY_PARAMETER key, float value);
        void setBool(SETTINGS_KEY_PARAMETER key, bool value);
        void eraseKey(SETTINGS_KEY_PARAMETER key);

        //Getters
        [[nodiscard]] SettingsTypes getType(SETTINGS_KEY_PARAMETER key) const;
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
        [[nodiscard]] std::string toXml() const;
        void fromXml(const std::string& xml);
    private:
        std::map<std::string, std::string> _strings {};
        std::map<std::string, int> _integers {};
        std::map<std::string, float> _floats {};
        std::map<std::string, bool> _bools {};
    };


    // Global ProjectSettings
    /// Resets the global instance of Settings
    /// \param settings Reference to new instance to be set as the global project settings
    void initProjectSettings(Settings& settings);
    /// Returns a reference to the global instance of Settings.
    /// \return A reference to the project-wide Settings instance.
    Settings& getProjectSettings();
}

#endif //SPC_PROJECT_PROJECTSETTINGS_H
