//
// Created by Lucas on 2-11-2022.
//

#include <exception>
#include <stdexcept>
#include <json/json.h>

#include "ProjectSettings.h"

namespace GolfEngine::Core{

    bool ProjectSettings::hasString(const std::string& key) const {
        return _strings.find(key) != _strings.end();
    }

    bool ProjectSettings::hasInteger(const std::string& key) const {
        return _integers.find(key) != _integers.end();
    }

    bool ProjectSettings::hasFloat(const std::string& key) const {
        return _floats.find(key) != _floats.end();
    }

    bool ProjectSettings::hasBool(const std::string& key) const {
        return _bools.find(key) != _bools.end();
    }

    ProjectSettingsTypes ProjectSettings::getType(const std::string& key) const {
        if(hasString(key)){
            return ProjectSettingsTypes::String;
        }
        else if(hasInteger(key)){
            return ProjectSettingsTypes::Integer;
        }
        else if(hasFloat(key)){
            return ProjectSettingsTypes::Float;
        }
        else if(hasBool(key)){
            return ProjectSettingsTypes::Boolean;
        }
        else{
            return ProjectSettingsTypes::Null;
        }
    }

    const std::string& ProjectSettings::getString(const std::string& key) const {
        if(hasString(key)){
            return _strings.at(key);
        }
        else{
            throw std::runtime_error {"No key of type String was found."};
        }
    }

    int ProjectSettings::getInteger(const std::string& key) const {
        if(hasInteger(key)){
            return _integers.at(key);
        }
        else{
            throw std::runtime_error {"No key of type Integer was found."};
        }
    }

    float ProjectSettings::getFloat(const std::string& key) const {
        if(hasFloat(key)){
            return _floats.at(key);
        }
        else{
            throw std::runtime_error {"No key of type Float was found."};
        }
    }

    bool ProjectSettings::getBool(const std::string& key) const {
        if(hasBool(key)){
            return _bools.at(key);
        }
        else{
            throw std::runtime_error {"No key of type Bool was found."};
        }
    }

    void ProjectSettings::setInteger(const std::string& key, int value) {
        if(!key.empty()){
            eraseKey(key);
            _integers[key] = value;
        }
    }

    void ProjectSettings::setBool(const std::string& key, bool value) {
        if(!key.empty()){
            eraseKey(key);
            _bools[key] = value;
        }
    }

    void ProjectSettings::setString(const std::string& key, const std::string& value) {
        if(!key.empty()){
            eraseKey(key);
            _strings[key] = value;
        }
    }

    void ProjectSettings::setFloat(const std::string& key, float value) {
        if(!key.empty()){
            eraseKey(key);
            _floats[key] = value;
        }
    }

    void ProjectSettings::eraseKey(const std::string& key) {
        _strings.erase(key);
        _floats.erase(key);
        _bools.erase(key);
        _integers.erase(key);
    }

    std::string ProjectSettings::toJson() const {
    }
}
