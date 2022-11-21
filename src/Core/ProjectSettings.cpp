//
// Created by Lucas on 2-11-2022.
//

#include "ProjectSettings.h"

namespace GolfEngine::Core{
    void ProjectSettings::setSettings(const std::string& key, const std::string& value) {
        if(!key.empty()){
            _settings[key] = value;
        }
    }

    bool ProjectSettings::hasSetting(const std::string& key) const {
        return _settings.find(key) != _settings.end();
    }

    std::string ProjectSettings::getSetting(const std::string& key) const {
        if(hasSetting(key)){
            return _settings.at(key);
        }
        else{
            //TODO throw exception on empty ProjectSettings record?
            return "";
        }
    }
}
