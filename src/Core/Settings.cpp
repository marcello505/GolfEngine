//
// Created by Lucas on 2-11-2022.
//

#include <exception>
#include <stdexcept>
#include <pugixml.hpp>
#include <sstream>
#include <memory>

#include "Settings.h"

//XMl keys
#define XML_ATTR_STRING "string"
#define XML_ATTR_INTEGER "integer"
#define XML_ATTR_FLOAT "float"
#define XML_ATTR_BOOL "bool"

namespace GolfEngine::Core{
    //Settings implementations
    bool Settings::hasString(const std::string& key) const {
        return _strings.find(key) != _strings.end();
    }

    bool Settings::hasInteger(const std::string& key) const {
        return _integers.find(key) != _integers.end();
    }

    bool Settings::hasFloat(const std::string& key) const {
        return _floats.find(key) != _floats.end();
    }

    bool Settings::hasBool(const std::string& key) const {
        return _bools.find(key) != _bools.end();
    }

    SettingsTypes Settings::getType(const std::string& key) const {
        if(hasString(key)){
            return SettingsTypes::String;
        }
        else if(hasInteger(key)){
            return SettingsTypes::Integer;
        }
        else if(hasFloat(key)){
            return SettingsTypes::Float;
        }
        else if(hasBool(key)){
            return SettingsTypes::Boolean;
        }
        else{
            return SettingsTypes::Null;
        }
    }

    const std::string& Settings::getString(const std::string& key) const {
        if(hasString(key)){
            return _strings.at(key);
        }
        else{
            throw std::runtime_error {"No key of type String was found."};
        }
    }

    int Settings::getInteger(const std::string& key) const {
        if(hasInteger(key)){
            return _integers.at(key);
        }
        else{
            throw std::runtime_error {"No key of type Integer was found."};
        }
    }

    float Settings::getFloat(const std::string& key) const {
        if(hasFloat(key)){
            return _floats.at(key);
        }
        else{
            throw std::runtime_error {"No key of type Float was found."};
        }
    }

    bool Settings::getBool(const std::string& key) const {
        if(hasBool(key)){
            return _bools.at(key);
        }
        else{
            throw std::runtime_error {"No key of type Bool was found."};
        }
    }

    void Settings::setInteger(const std::string& key, int value) {
        if(!key.empty()){
            eraseKey(key);
            _integers[key] = value;
        }
    }

    void Settings::setBool(const std::string& key, bool value) {
        if(!key.empty()){
            eraseKey(key);
            _bools[key] = value;
        }
    }

    void Settings::setString(const std::string& key, const std::string& value) {
        if(!key.empty()){
            eraseKey(key);
            _strings[key] = value;
        }
    }

    void Settings::setFloat(const std::string& key, float value) {
        if(!key.empty()){
            eraseKey(key);
            _floats[key] = value;
        }
    }

    void Settings::eraseKey(const std::string& key) {
        _strings.erase(key);
        _floats.erase(key);
        _bools.erase(key);
        _integers.erase(key);
    }

    std::string Settings::toXml() const {
        pugi::xml_document doc {};

        //Insert strings
        for(const auto& keyValue : _strings){
            doc.append_child(keyValue.first.c_str())
                .append_attribute(XML_ATTR_STRING)
                .set_value(keyValue.second.c_str());
        }

        //Insert integers
        for(const auto& keyValue : _integers){
            doc.append_child(keyValue.first.c_str())
                    .append_attribute(XML_ATTR_INTEGER)
                    .set_value(keyValue.second);
        }

        //Insert float
        for(const auto& keyValue : _floats){
            doc.append_child(keyValue.first.c_str())
                    .append_attribute(XML_ATTR_FLOAT)
                    .set_value(keyValue.second);
        }

        //Insert bool
        for(const auto& keyValue : _bools){
            doc.append_child(keyValue.first.c_str())
                    .append_attribute(XML_ATTR_BOOL)
                    .set_value(keyValue.second);
        }

        std::stringstream resultStream {};
        doc.save(resultStream);
        return resultStream.str();
    }

    void Settings::fromXml(const std::string& xml){
        pugi::xml_document doc {};
        if(!doc.load_string(xml.c_str())){
            throw std::runtime_error("Settings::fromXml() cannot parse the given string to XML");
        }

        //Read and set contents
        for(auto& xmlChild : doc.children()){
            auto key = xmlChild.name();
            auto value = xmlChild.first_attribute();
            auto type = std::string{value.name()};

            if(type == XML_ATTR_BOOL){
                setBool(key, value.as_bool());
            }
            else if(type == XML_ATTR_INTEGER){
                setInteger(key, value.as_int());
            }
            else if(type == XML_ATTR_STRING){
                setString(key, value.as_string());
            }
            else if(type == XML_ATTR_FLOAT){
                setFloat(key, value.as_float());
            }
        }
    }

    //ProjectSettings
    std::unique_ptr<Settings> _projectSettings = std::make_unique<Settings>();

    Settings& getProjectSettings() {
        return *_projectSettings;
    }
}
