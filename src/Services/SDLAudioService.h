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
    SDLAudioService(int amountOfChannels);
    void playOnChannel(int channel, const std::string& path, float volume) override;
    void preloadAudio(const char* path) override;
    void resumeAudio(int channel) override;
    void pauseAudio(int channel) override;
    void haltAudio(int channel) override;
    void setVolumeChannel(int channel, float volume) override;
    void setGlobalVolume(float volume) override;
    void clearAudio() override;
private:
    bool channelExists(int channel);
    int _amountOfChannels;
    std::map<std::string, Mix_Chunk*> _soundEffects;
    std::map<std::string, Mix_Music*> _music;
};


#endif //SPC_PROJECT_SDLAUDIOSERVICE_H
