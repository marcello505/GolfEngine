//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLAUDIOSERVICE_H
#define SPC_PROJECT_SDLAUDIOSERVICE_H

#include "Abstracts/AudioService.h"

#include <SDL_mixer.h>
#include <map>
#include <array>

class SDLAudioService : public AudioService {
public:
    SDLAudioService(); //constructor
    void playSfx(const std::string& path, float volume) override;
    void playMusic(const std::string& path, float volume, bool loop) override;
    void pauseMusic() override;
    void resumeMusic() override;
    void stopMusic() override;
    void stopSfx() override;

    // Volume
    float getMasterVolume() override;
    float getMusicVolume() override;
    float getSfxVolume() override;
    /// Sets the _musicVolume field and immediatly updates the volume of the current music.
    /// \param volume a value between 0.0 and 1.0
    void setMusicVolume(float volume) override;
    /// Sets the _sfxVolume field, which gets factored in the next time an Sfx plays.
    /// \param volume a value between 0.0 and 1.0
    void setSfxVolume(float volume) override;
    /// Sets the master volume by calling Mix_VolumeMaster
    /// \param volume
    void setMasterVolume(float volume) override;


    void preloadSfx(const std::string& path) override;
    void preloadMusic(const std::string& path) override;
    void clearCache() override;
    bool isMusicPlaying() override;
    bool isMusicPaused() override;
    void toggleMusic() override;

private:
    //Fields
    float _masterVolume {1.0f};
    float _musicVolume {1.0f};
    float _musicFragmentVolume {1.0f};
    float _sfxVolume {1.0f};
    std::array<float, 8> _sfxFragmentsVolume {};
    std::map<std::string, Mix_Chunk*> _cachedChunks {};
    std::map<std::string, Mix_Music*> _cachedMusic {};

    //Methods
    void updateMusicVolume();
    void updateSfxVolume(int channel);
    void updateSfxVolume();
    Mix_Chunk* getChunk(const std::string& path);
    Mix_Music* getMusic(const std::string& path);
    bool hasCachedChunk(const std::string& path);
    bool hasCachedMusic(const std::string& path);
    float clampFloat01(float value);
};


#endif //SPC_PROJECT_SDLAUDIOSERVICE_H
