//
// Created by jaaps on 02/11/2022.
//

#include "AudioSource.h"
#include "Services/Singletons/AudioSingleton.h"

namespace GolfEngine::Scene::Components{
    void AudioSource::play(const std::string& sound, bool looping) {
        if(GolfEngine::Services::Audio::hasService() && _active){
            // Find sound path using key
            auto result = _sounds.find(sound);
            if(result == _sounds.end()) { return; }

            if(_isMusic){
                GolfEngine::Services::Audio::getService()->playMusic(result->second, volume, looping);
            }
            else{
                GolfEngine::Services::Audio::getService()->playSfx(result->second, volume, looping);
            }
        }
    }

    void AudioSource::stop(const std::string& sound) {
        if(GolfEngine::Services::Audio::hasService() && _active){
            // Find sound path using key
            auto result = _sounds.find(sound);
            if(result == _sounds.end()) { return; }

            if(_isMusic){
                GolfEngine::Services::Audio::getService()->stopMusic();
            }
            else{
                GolfEngine::Services::Audio::getService()->stopSfx(result->second);
            }
        }
    }

    void AudioSource::onStart() {
        if(_active){
            if(Services::Audio::hasService()){
                for(auto& sound : _sounds){
                    if(_isMusic){
                        Services::Audio::getService()->preloadMusic(sound.second);
                    }
                    else{
                        Services::Audio::getService()->preloadSfx(sound.second);
                    }
                }
            }

            if(_playOnAwake && !_sounds.empty()){
                play(_sounds.begin()->second, _loopOnAwake);
            }
        }
    }

    void AudioSource::onUpdate() {

    }

    void AudioSource::onRemove() {
    }

    bool AudioSource::getActive() {
        return _active;
    }

    void AudioSource::setActive(bool active) {
        _active = active;
    }

    void AudioSource::setParentGameObject(GameObject& gameObject) {
        _parent = gameObject;
    }

    std::unique_ptr<ISnapshot> AudioSource::saveSnapshot() {
        auto result = std::make_unique<Snapshot>();
        result->volume = volume;
        return result;
    }

    void AudioSource::loadSnapshot(const ISnapshot& rawSnapshot) {
        auto& snapshot = (Snapshot&)rawSnapshot;

        volume = snapshot.volume;
    }

    void AudioSource::addSound(const std::string& sound, const std::string& path) {
        // Check if an entry with the name already exists, if so delete it first to overwrite it
        auto existingEntry = _sounds.find(sound);
        if(existingEntry != _sounds.end())
            _sounds.erase(existingEntry);

        // Add entry to sounds map
        _sounds.insert({sound, path});
    }

}

