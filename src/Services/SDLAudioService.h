//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLAUDIOSERVICE_H
#define SPC_PROJECT_SDLAUDIOSERVICE_H

#include "Abstracts/AudioService.h"

#include <SDL_mixer.h>
#include <map>
#include <array>

namespace GolfEngine::Services::Audio {
    class SDLAudioService : public AudioService {
    public:
        //Life Cycles
        void init() override;
        void free() override;

        // Audio Controls
        void playSfx(const std::string &path, float volume, bool loop) override;
        void playMusic(const std::string &path, float volume, bool loop) override;
        void pauseMusic() override;
        void resumeMusic() override;
        void toggleMusic() override;
        void stopMusic() override;
        void stopSfx() override;
        void stopSfx(const std::string &path) override;

        // Volume
        float getMasterVolume() override;
        float getMusicVolume() override;
        float getSfxVolume() override;
        void setMusicVolume(float volume) override;
        void setSfxVolume(float volume) override;
        void setMasterVolume(float volume) override;

        // Cache Methods
        void preloadSfx(const std::string &path) override;
        void preloadMusic(const std::string &path) override;

        // Getters
        bool isMusicPlaying() override;
        bool isMusicPaused() override;

    private:
        //Fields
        float _masterVolume{1.0f};
        float _musicVolume{1.0f};
        float _musicFragmentVolume{1.0f};
        float _sfxVolume{1.0f};
        std::array<float, 8> _sfxFragmentsVolume{};
        std::map<std::string, Mix_Chunk *> _cachedChunks{};
        std::map<std::string, Mix_Music *> _cachedMusic{};

        // Helper Methods
        void clearCache() override;
        void updateMusicVolume();
        void updateSfxVolume(int channel);
        void updateSfxVolume();
        Mix_Chunk *getChunk(const std::string &path);
        Mix_Music *getMusic(const std::string &path);
        bool hasCachedChunk(const std::string &path);
        bool hasCachedMusic(const std::string &path);
        float clampFloat01(float value);
    };
}

#endif //SPC_PROJECT_SDLAUDIOSERVICE_H
