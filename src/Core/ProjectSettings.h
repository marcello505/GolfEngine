//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_PROJECTSETTINGS_H
#define SPC_PROJECT_PROJECTSETTINGS_H

#include <string>
#include <map>

namespace GolfEngine::Core{
    class ProjectSettings {
    public:
        void setSettings(const std::string& key, const std::string& value);
        [[nodiscard]] bool hasSetting(const std::string& key) const;
        [[nodiscard]] std::string getSetting(const std::string& key) const;
    private:
        std::map<std::string, std::string> _settings {};
    };

}



#endif //SPC_PROJECT_PROJECTSETTINGS_H
