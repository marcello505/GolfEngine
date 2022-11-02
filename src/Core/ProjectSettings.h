//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_PROJECTSETTINGS_H
#define SPC_PROJECT_PROJECTSETTINGS_H

#include <string>
#include <map>

class ProjectSettings {
private:
    std::map<std::string, std::string> settings;
public:
    void setSettings(const std::string& key, const std::string& value);
    void getSettings(const std::string& key) const;
};


#endif //SPC_PROJECT_PROJECTSETTINGS_H
