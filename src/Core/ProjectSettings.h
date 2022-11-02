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
    void setSettings(std::string key, std::string value);
    void getSettings(std::string key, std::string value) const;
};


#endif //SPC_PROJECT_PROJECTSETTINGS_H
