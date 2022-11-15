//
// Created by conner on 11/2/2022.
//

#include "SDLAudioService.h"
#include <iostream>

SDLAudioService::SDLAudioService(int amountOfChannels)
{
    _amountOfChannels = amountOfChannels;
    bool m_SoundInitilized = false;
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = _amountOfChannels;
    int audio_buffers = 4096;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    {
        std::cout << "Couldn't init audio: %s", Mix_GetError();
        exit(-1);
    }
    else
    {
        m_SoundInitilized = true;
    }

}

void SDLAudioService::playOnChannel(int channel, const std::string &path, float volume)
{
    setVolumeChannel(channel, volume);
    if (!(_soundEffects.count(path)) > 0 && channelExists(channel))
    {
        std::cout << "Sound or channel doesnt exist.\n";
        return;
    }
    Mix_PlayChannel(channel, _soundEffects.find(path)->second, 0);
}

void SDLAudioService::preloadAudio(const char* path)
{
    Mix_Chunk* tmpChunk = Mix_LoadWAV(path);

    if (tmpChunk != nullptr)
    {
        _soundEffects.insert(std::pair<std::string, Mix_Chunk*>(path, tmpChunk));
        std::cout << " Sound is Ready, path: " << path << '\n';
    }
    else
    {
        std::cout << "Couldn't init audio: " << Mix_GetError() << '\n';
    }
}

void SDLAudioService::resumeAudio(int channel)
{
    if(channelExists(channel)){
        Mix_Resume(channel);
    }

}

void SDLAudioService::pauseAudio(int channel)
{
    if(channelExists(channel)) {
        Mix_Pause(channel);
    }
}

void SDLAudioService::haltAudio(int channel)
{
    if(channelExists(channel)) {
        Mix_HaltChannel(channel);
    }
}

void SDLAudioService::setVolumeChannel(int channel, float volume)
{
    if(channelExists(channel)) {
        Mix_Volume(channel, volume);
    }
}

void SDLAudioService::setGlobalVolume(float volume)
{
    Mix_Volume(-1, volume);
}

void SDLAudioService::clearAudio()
{
}

bool SDLAudioService::channelExists(int channel)
{
    return channel > -1 && channel < _amountOfChannels;
}
