#include <doctest.h>

#include "Scene/Components/AudioSource.h"
#include "Services/Abstracts/AudioService.h"
#define GOLFENGINE_SINGLETON_PRIVATE
#include "Services/Singletons/AudioSingleton.h"

namespace AudioSourceTests{
    class DummyAudioService : public AudioService{
    public:
        bool calledPlayMusic {false};
        bool calledPlaySfx {false};
        bool calledStopMusic {false};
        bool calledStopSfx {false};
        bool calledPreloadMusic {false};
        bool calledPreloadSfx {false};

        //Methods
        void resetCalledFields(){
            calledPlayMusic = false;
            calledPlaySfx = false;
            calledStopMusic = false;
            calledStopSfx = false;
            calledPreloadMusic = false;
            calledPreloadSfx = false;
        }

        //Overridden methods
        void init() override {}
        void free() override {}
        void playSfx(const std::string& path, float volume, bool loop) override {calledPlaySfx = true;}
        void playMusic(const std::string& path, float volume, bool loop) override {calledPlayMusic = true;}
        void pauseMusic() override {}
        void resumeMusic() override {}
        void toggleMusic() override {}
        void stopMusic() override {calledStopMusic = true;}
        void stopSfx() override {calledStopSfx = true;}
        void stopSfx(const std::string& path) override {calledStopSfx = true;}
        float getMasterVolume() override { return 0; }
        float getMusicVolume() override {return 0;}
        float getSfxVolume() override {return 0;}
        void setMasterVolume(float volume) override {}
        void setMusicVolume(float volume) override {}
        void setSfxVolume(float volume) override {}
        void preloadSfx(const std::string& path) override {calledPreloadSfx = true;}
        void preloadMusic(const std::string& path) override {calledPreloadMusic = true;}
        void clearCache() override {}
        bool isMusicPlaying() override {return false;}
        bool isMusicPaused() override {return false;}
    };
}

TEST_SUITE("Components/AudioSource"){
#define DUMMY_AUDIO_PATH "FakeSong.wav"

    AudioSourceTests::DummyAudioService* audioService = new AudioSourceTests::DummyAudioService{};

    TEST_CASE("Set AudioService"){
        GolfEngine::Services::Audio::setService(audioService);
    }

    TEST_CASE("onStart() preloads the audio"){
        //Arrange
        GolfEngine::Scene::Components::AudioSource musicSource {true};
        musicSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);
        GolfEngine::Scene::Components::AudioSource sfxSource {false};
        sfxSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);

        SUBCASE("Sfx"){
            sfxSource.onStart();
            CHECK(audioService->calledPreloadSfx);
        }
        SUBCASE("Music"){
            musicSource.onStart();
            CHECK(audioService->calledPreloadMusic);
        }
        audioService->resetCalledFields();
    }

    TEST_CASE("play() calls the corresponding play method in AudioService"){
        //Arrange
        GolfEngine::Scene::Components::AudioSource musicSource {true};
        musicSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);
        GolfEngine::Scene::Components::AudioSource sfxSource {false};
        sfxSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);

        SUBCASE("Sfx"){
            sfxSource.play(DUMMY_AUDIO_PATH);
            CHECK(audioService->calledPlaySfx);
        }
        SUBCASE("Music"){
            musicSource.play(DUMMY_AUDIO_PATH);
            CHECK(audioService->calledPlayMusic);
        }
        audioService->resetCalledFields();
    }

    TEST_CASE("stop() calls the corresponding stop method in AudioService"){
        //Arrange
        GolfEngine::Scene::Components::AudioSource musicSource {true};
        musicSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);
        GolfEngine::Scene::Components::AudioSource sfxSource {false};
        sfxSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);

        SUBCASE("Sfx"){
            sfxSource.stop(DUMMY_AUDIO_PATH);
            CHECK(audioService->calledStopSfx);
        }
        SUBCASE("Music"){
            musicSource.stop(DUMMY_AUDIO_PATH);
            CHECK(audioService->calledStopMusic);
        }
        audioService->resetCalledFields();
    }

    TEST_CASE("onStart() plays the audio when PlayOnAwake is true"){
        //Arrange
        GolfEngine::Scene::Components::AudioSource musicSource {true, true};
        musicSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);
        GolfEngine::Scene::Components::AudioSource sfxSource {false, true};
        sfxSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);

        SUBCASE("Sfx"){
            sfxSource.onStart();
            CHECK(audioService->calledPlaySfx);
        }
        SUBCASE("Music"){
            musicSource.onStart();
            CHECK(audioService->calledPlayMusic);
        }
        audioService->resetCalledFields();
    }

    TEST_CASE("when inactive, none of the AudioService methods get called"){
        //Arrange
        GolfEngine::Scene::Components::AudioSource musicSource {true, true};
        musicSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);
        GolfEngine::Scene::Components::AudioSource sfxSource {false, true};
        sfxSource.addSound(DUMMY_AUDIO_PATH, DUMMY_AUDIO_PATH);

        SUBCASE("Sfx"){
            sfxSource.setActive(false);
            sfxSource.onStart();
            sfxSource.play(DUMMY_AUDIO_PATH);
            sfxSource.stop(DUMMY_AUDIO_PATH);
            CHECK_FALSE(sfxSource.getActive());
            CHECK_FALSE(audioService->calledPlaySfx);
            CHECK_FALSE(audioService->calledStopSfx);
            CHECK_FALSE(audioService->calledPreloadSfx);
        }
        SUBCASE("Music"){
            musicSource.setActive(false);
            musicSource.onStart();
            musicSource.play(DUMMY_AUDIO_PATH);
            musicSource.stop(DUMMY_AUDIO_PATH);
            CHECK_FALSE(musicSource.getActive());
            CHECK_FALSE(audioService->calledPlayMusic);
            CHECK_FALSE(audioService->calledStopMusic);
            CHECK_FALSE(audioService->calledPreloadMusic);
        }
        audioService->resetCalledFields();
    }

    TEST_CASE("UnSet AudioService"){
        GolfEngine::Services::Audio::setService(nullptr);
    }

}