//
// Created by conner on 11/2/2022.
//

#include "SDLAudioService.h"
#include <SDL_mixer.h>
#include <iostream>
#include <sstream>

class Chunk_Wrapper{
public:
    explicit Chunk_Wrapper(Mix_Chunk* c) : chunk{c}{}
    Mix_Chunk* chunk;
};

class Music_Wrapper{
public:
    explicit Music_Wrapper(Mix_Music* m) : music{m}{}
    Mix_Music* music;
};

void SDLAudioService::playSfx(const std::string& path, float volume, bool loop) {
    //Play sfx
    Mix_Chunk* chunk = getChunk(path)->chunk;
    int channelNr = Mix_PlayChannel(-1, chunk, loop ? -1 : 0);

    if(channelNr != -1){
        _sfxFragmentsVolume[channelNr] = volume;
        updateSfxVolume(channelNr);
    }
}

void SDLAudioService::playMusic(const std::string& path, float volume, bool loop) {
    Mix_Music* music = getMusic(path)->music;
    _musicFragmentVolume = clampFloat01(volume);

    Mix_PlayMusic(music, loop ? -1 : 0);
    updateMusicVolume();
}


void SDLAudioService::pauseMusic() {
    Mix_PauseMusic();
}

void SDLAudioService::resumeMusic() {
    Mix_ResumeMusic();
}

void SDLAudioService::stopMusic() {
    Mix_HaltMusic();
}

void SDLAudioService::stopSfx() {
    Mix_HaltChannel(-1);
}

float SDLAudioService::getMasterVolume() {
    return _masterVolume;
}

float SDLAudioService::getMusicVolume() {
    return _musicVolume;
}

float SDLAudioService::getSfxVolume() {
    return _sfxVolume;
}

float SDLAudioService::clampFloat01(float value) {
    if(value < 0.0f) value = 0.0f;
    if(value > 1.0f) value = 1.0f;
    return value;
}

void SDLAudioService::setMasterVolume(float volume)
{
    _masterVolume = clampFloat01(volume);
    updateMusicVolume();
    updateSfxVolume();
}

void SDLAudioService::setMusicVolume(float volume) {
    _musicVolume = clampFloat01(volume);
    updateMusicVolume();
}

void SDLAudioService::setSfxVolume(float volume) {
    _sfxVolume = clampFloat01(volume);
    updateSfxVolume();
}

void SDLAudioService::preloadSfx(const std::string& path) {
    if(hasCachedChunk(path)){
        //Already loaded, thus return.
        return;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if(chunk){
        _cachedChunks[path] = new Chunk_Wrapper{chunk};
    }
    else{
        std::stringstream errMessage {};
        errMessage << "Couldn't load Sfx: " << Mix_GetError();
        throw std::runtime_error(errMessage.str());
    }
}

void SDLAudioService::preloadMusic(const std::string& path) {
    if(hasCachedMusic(path)){
        //Already loaded, thus return.
        return;
    }

    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if(music){
        _cachedMusic[path] = new Music_Wrapper{music};
    }
    else{
        std::stringstream errMessage {};
        errMessage << "Couldn't load music: " << Mix_GetError();
        throw std::runtime_error(errMessage.str());
    }
}

void SDLAudioService::clearCache() {
    for(auto& item : _cachedChunks){
        Mix_FreeChunk(item.second->chunk);
    }
    _cachedChunks.clear();

    for(auto& item : _cachedMusic){
        Mix_FreeMusic(item.second->music);
    }
    _cachedMusic.clear();
}

bool SDLAudioService::isMusicPlaying() {
    return Mix_PlayingMusic() == 1;
}

bool SDLAudioService::isMusicPaused() {
    return Mix_PausedMusic() == 1;
}

bool SDLAudioService::hasCachedChunk(const std::string& path) {
    return _cachedChunks.find(path) != _cachedChunks.end();
}

bool SDLAudioService::hasCachedMusic(const std::string& path) {
    return _cachedMusic.find(path) != _cachedMusic.end();
}

Chunk_Wrapper* SDLAudioService::getChunk(const std::string& path) {
    if(!hasCachedChunk(path)){
        //Not cached
        preloadSfx(path);
    }
    return _cachedChunks[path];
}

Music_Wrapper* SDLAudioService::getMusic(const std::string& path) {
    if(!hasCachedMusic(path)){
        //Not cached
        preloadMusic(path);
    }
    return _cachedMusic[path];
}

void SDLAudioService::toggleMusic() {
    if(isMusicPaused()){
        resumeMusic();
    }
    else{
        pauseMusic();
    }
}

void SDLAudioService::updateMusicVolume(){
    Mix_VolumeMusic(128 * _masterVolume * _musicVolume * _musicFragmentVolume);
}

void SDLAudioService::updateSfxVolume(int channel) {
    Mix_Volume(channel, 128 * _masterVolume * _sfxVolume * _sfxFragmentsVolume[channel]);
}

void SDLAudioService::updateSfxVolume() {
    for(int i = 0; i < _sfxFragmentsVolume.max_size(); i++){
        updateSfxVolume(i);
    }
}

void SDLAudioService::stopSfx(const std::string& path) {
    if(!hasCachedChunk(path)){
        //Sfx isn't loaded, thus nothing to stop.
        return;
    }

    Mix_Chunk* chunk = getChunk(path)->chunk;
    for(int i = 0; i < MIX_CHANNELS; i++){
        if(Mix_GetChunk(i) == chunk){
            Mix_HaltChannel(i);
        }
    }
}

void SDLAudioService::init() {
    int frequency = MIX_DEFAULT_FREQUENCY;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = MIX_DEFAULT_CHANNELS; //channels for use
    int chunk_size = 2048; //chunksize

    if (Mix_OpenAudio(frequency, audio_format, audio_channels, chunk_size) != 0) //Open the default audio device for playback
    {
        std::cout << "Couldn't init audio: %s", Mix_GetError();
        exit(-1);
    }

    //Set all _sfxFragmentsVolume to a default of 1.0f
    for(int i = 0; i < _sfxFragmentsVolume.max_size(); ++i){
        _sfxFragmentsVolume[i] = 1.0f;
    }
}

void SDLAudioService::free() {
    clearCache();
    Mix_CloseAudio();
}
