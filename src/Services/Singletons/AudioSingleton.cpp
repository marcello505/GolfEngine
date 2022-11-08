#include "AudioSingleton.h"
#include <memory>

namespace GolfEngine::Services::Audio{
    std::unique_ptr<AudioService> globalAudioInstance {};

    AudioService* getService() {
        if(globalAudioInstance){
            return globalAudioInstance.get();
        }
        else{
            return nullptr;
        }
    }

    void setService(AudioService* service) {
        globalAudioInstance.reset(service);
    }

    bool hasService() {
        return (bool)globalAudioInstance;
    }

}
