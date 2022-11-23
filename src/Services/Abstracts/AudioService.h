//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_AUDIOSERVICE_H
#define SPC_PROJECT_AUDIOSERVICE_H

#include <string>

class AudioService{
public:
    // Audio Controls Methods
    virtual void playSfx(const std::string& path, float volume, bool loop) = 0;
    virtual void playMusic(const std::string& path, float volume, bool loop) = 0;
    virtual void pauseMusic() = 0;
    virtual void resumeMusic() = 0;
    virtual void toggleMusic() = 0;
    virtual void stopMusic() = 0;
    virtual void stopSfx() = 0;
    virtual void stopSfx(const std::string& path) = 0;

    // Volume Methods
    virtual float getMasterVolume() = 0;
    virtual float getMusicVolume() = 0;
    virtual float getSfxVolume() = 0;
    virtual void setMasterVolume(float volume) = 0;
    virtual void setMusicVolume(float volume) = 0;
    virtual void setSfxVolume(float volume) = 0;

    // Cache Methods
    virtual void preloadSfx(const std::string& path) = 0;
    virtual void preloadMusic(const std::string& path) = 0;
    virtual void clearCache() = 0;

    // Getters and boolean Methods
    virtual bool isMusicPlaying() = 0;
    virtual bool isMusicPaused() = 0;
};


#endif //SPC_PROJECT_AUDIOSERVICE_H
