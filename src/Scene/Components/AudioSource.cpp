//
// Created by jaaps on 02/11/2022.
//

#include "AudioSource.h"
#include "Services/Singletons/AudioSingleton.h"

namespace GolfEngine::Scene::Components{
    void AudioSource::play(bool looping) {
        if(GolfEngine::Services::Audio::hasService() && _active){
            if(_isMusic){
                GolfEngine::Services::Audio::getService()->playMusic(_audioPath, volume, looping);
            }
            else{
                GolfEngine::Services::Audio::getService()->playSfx(_audioPath, volume, looping);
            }
        }
    }

    void AudioSource::stop() {
        if(GolfEngine::Services::Audio::hasService() && _active){
            if(_isMusic){
                GolfEngine::Services::Audio::getService()->stopMusic();
            }
            else{
                GolfEngine::Services::Audio::getService()->stopSfx(_audioPath);
            }
        }
    }

    void AudioSource::onStart() {
        if(_active){
            if(Services::Audio::hasService()){
                if(_isMusic){
                    Services::Audio::getService()->preloadMusic(_audioPath);
                }
                else{
                    Services::Audio::getService()->preloadSfx(_audioPath);
                }
            }

            if(_playOnAwake){
                play(_loopOnAwake);
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

}

