//
// Created by conner on 11/2/2022.
//

#include "SDLAudioService.h"
#include <iostream>

SDLAudioService::SDLAudioService(int amountOfChannels)
{
    _amountOfChannels = amountOfChannels;
    int frequency = 48000; //frequency, set to 48000 as mentioned in https://wiki.libsdl.org/SDL_mixer/Mix_OpenAudioDevice as a reasonable default.
    Uint16 audio_format = AUDIO_F32SYS ; //format
    int audio_channels = _amountOfChannels; //channels for use
    int chunk_size = 2048; //chunksize

    if (Mix_OpenAudio(frequency, audio_format, audio_channels, chunk_size) != 0) //Open the default audio device for playback
    {
        std::cout << "Couldn't init audio: %s", Mix_GetError();
        exit(-1);
    }

}

void SDLAudioService::playOnChannel(int channel, const std::string &path, float volume)
{
    if (!(_sounds.count(path)) > 0 && channelExists(channel)) //check if chunk and sound exist
    {
        std::cout << "Sound or channel doesnt exist.\n";
        return;
    }
    Mix_VolumeChunk(_sounds.find(path)->second, volume); // set volume of chunk
    Mix_PlayChannel(channel, _sounds.find(path)->second, 0); // play chunk on channel, without loop
}

void SDLAudioService::preloadAudio(const std::string path)
{
    Mix_Chunk* tmpChunk = Mix_LoadWAV(path.c_str()); // load in chunk with path

    if (tmpChunk != nullptr) //if chunk is made succesfully
    {
        _sounds.insert(std::pair<std::string, Mix_Chunk*>(path, tmpChunk));  // insert chunk into list
        std::cout << " Sound is Ready, path: " << path << '\n';
    }
    else
    {
        std::cout << "Couldn't init audio: " << Mix_GetError() << '\n';
    }
}

void SDLAudioService::resumeAudio(int channel)
{
    if(channelExists(channel)){ // if channel exists
        Mix_Resume(channel); // resume audio
    }
}

void SDLAudioService::pauseAudio(int channel)
{
    if(channelExists(channel)) { // if channel exists
        Mix_Pause(channel); // pause audio
    }
}

void SDLAudioService::haltAudio(int channel)
{
    if(channelExists(channel)) { // if channel exists
        Mix_HaltChannel(channel); // halt audio
    }
}

void SDLAudioService::setVolumeChannel(int channel, float volume)
{
    if(channelExists(channel)) // if channel exists
    {
        Mix_Volume(channel, volume); // set volume of channel
    }
}

void SDLAudioService::setGlobalVolume(float volume)
{
    Mix_Volume(-1, volume); // set global volume
}

void SDLAudioService::clearAudio()
{
    _sounds.clear(); // clear audiolist
}

bool SDLAudioService::channelExists(int channel)
{
    return channel > -1 && channel < _amountOfChannels; // channel is in range between 0 and amount of channels
}
