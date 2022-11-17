//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_AUDIOSERVICE_H
#define SPC_PROJECT_AUDIOSERVICE_H

#include <string>

class AudioService{
public:
    virtual void playOnChannel(int channel, const std::string& path) = 0;
    virtual void preloadAudio(const char* path) = 0;
    virtual void resumeAudio(int channel) = 0;
    virtual void pauseAudio(int channel) = 0;
    virtual void haltAudio(int channel) = 0;
    virtual void setVolumeChannel(int channel, float volume) = 0;
    virtual void setGlobalVolume(float volume) = 0;
    virtual void clearAudio() = 0;
};


#endif //SPC_PROJECT_AUDIOSERVICE_H
