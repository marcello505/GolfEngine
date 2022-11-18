//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLAUDIOSERVICE_H
#define SPC_PROJECT_SDLAUDIOSERVICE_H

#include "Abstracts/AudioService.h"
#include <SDL_mixer.h>
#include <map>
#include <SDL.h>
class SDLAudioService : public AudioService {
public:
    SDLAudioService(int amountOfChannels); //constructor
    void playOnChannel(int channel, const std::string& path, float volume) override; //play on channel with volume
    void preloadAudio(const char* path) override; // setup audio
    void resumeAudio(int channel) override; // resume paused audio
    void pauseAudio(int channel) override; // pause audio
    void haltAudio(int channel) override; // stop audio
    void setVolumeChannel(int channel, float volume) override; // set volume of channel
    void setGlobalVolume(float volume) override; // set global volume (all channels)
    void clearAudio() override; // clear audiolist
private:
    bool channelExists(int channel); // check if channel exists
    int _amountOfChannels; // local variable for the amount of channels
    std::map<std::string, Mix_Chunk*> _sounds; // audiolist
};


#endif //SPC_PROJECT_SDLAUDIOSERVICE_H
