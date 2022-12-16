//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLAUDIOSERVICE_H
#define SPC_PROJECT_SDLAUDIOSERVICE_H

#include "Abstracts/AudioService.h"

#include <map>
#include <array>

// Forward declaration
class Chunk_Wrapper;
class Music_Wrapper;

class SDLAudioService : public AudioService {
public:
    //Life Cycles
    /// Initializes the audio device, automatically called by GameLoop
    void init() override;
    /// Closes the audio device and clears cache, automatically called by GameLoop
    void free() override;

    // Audio Controls
    void playSfx(const std::string& path, float volume, bool loop) override;
    void playMusic(const std::string& path, float volume, bool loop) override;
    void pauseMusic() override;
    void resumeMusic() override;
    void stopMusic() override;
    void stopSfx() override;

    // Volume
    float getMasterVolume() override;
    float getMusicVolume() override;
    float getSfxVolume() override;
    /// Sets the _musicVolume field and updates the current volume of Music.
    /// \param volume a value between 0.0 and 1.0, used as a factor to calculate volume.
    void setMusicVolume(float volume) override;
    /// Sets the _sfxVolume field and updates the current volume of Sound effects.
    /// \param volume a value between 0.0 and 1.0, used as a factor to calculate volume.
    void setSfxVolume(float volume) override;
    /// Sets the _masterVolume field and updates the current volume of all audio.
    /// \param volume a value between 0.0 and 1.0, used as a factor to calculate volume.
    void setMasterVolume(float volume) override;
    /// Loads in the audio file as a sound effect, automatically called for play methods when neccesary.
    /// \param path path to the audio file.
    void preloadSfx(const std::string& path) override;
    /// Loads in the audio file as music, automatically called for play methods when neccesary.
    /// \param path path to the audio file.
    void preloadMusic(const std::string& path) override;
    void clearCache() override;
    bool isMusicPlaying() override;
    bool isMusicPaused() override;
    void toggleMusic() override;

    void stopSfx(const std::string& path) override;

private:
    //Fields
    float _masterVolume {1.0f};
    float _musicVolume {1.0f};
    float _musicFragmentVolume {1.0f};
    float _sfxVolume {1.0f};
    std::array<float, 8> _sfxFragmentsVolume {};
    std::map<std::string, Chunk_Wrapper*> _cachedChunks {};
    std::map<std::string, Music_Wrapper*> _cachedMusic {};

    //Methods
    void updateMusicVolume();
    void updateSfxVolume(int channel);
    void updateSfxVolume();
    Chunk_Wrapper* getChunk(const std::string& path);
    Music_Wrapper* getMusic(const std::string& path);
    bool hasCachedChunk(const std::string& path);
    bool hasCachedMusic(const std::string& path);
    float clampFloat01(float value);
};


#endif //SPC_PROJECT_SDLAUDIOSERVICE_H
