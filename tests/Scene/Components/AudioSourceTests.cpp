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
        GolfEngine::Scene::Components::AudioSource musicSource {DUMMY_AUDIO_PATH, true};
        GolfEngine::Scene::Components::AudioSource sfxSource {DUMMY_AUDIO_PATH, false};

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
        GolfEngine::Scene::Components::AudioSource musicSource {DUMMY_AUDIO_PATH, true};
        GolfEngine::Scene::Components::AudioSource sfxSource {DUMMY_AUDIO_PATH, false};

        SUBCASE("Sfx"){
            sfxSource.play();
            CHECK(audioService->calledPlaySfx);
        }
        SUBCASE("Music"){
            musicSource.play();
            CHECK(audioService->calledPlayMusic);
        }
        audioService->resetCalledFields();
    }

    TEST_CASE("stop() calls the corresponding stop method in AudioService"){
        //Arrange
        GolfEngine::Scene::Components::AudioSource musicSource {DUMMY_AUDIO_PATH, true};
        GolfEngine::Scene::Components::AudioSource sfxSource {DUMMY_AUDIO_PATH, false};

        SUBCASE("Sfx"){
            sfxSource.stop();
            CHECK(audioService->calledStopSfx);
        }
        SUBCASE("Music"){
            musicSource.stop();
            CHECK(audioService->calledStopMusic);
        }
        audioService->resetCalledFields();
    }

    TEST_CASE("onStart() plays the audio when PlayOnAwake is true"){
        //Arrange
        GolfEngine::Scene::Components::AudioSource musicSource {DUMMY_AUDIO_PATH, true, true};
        GolfEngine::Scene::Components::AudioSource sfxSource {DUMMY_AUDIO_PATH, false, true};

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
        GolfEngine::Scene::Components::AudioSource musicSource {DUMMY_AUDIO_PATH, true};
        GolfEngine::Scene::Components::AudioSource sfxSource {DUMMY_AUDIO_PATH, false};

        SUBCASE("Sfx"){
            sfxSource.setActive(false);
            sfxSource.onStart();
            sfxSource.play();
            sfxSource.stop();
            CHECK_FALSE(sfxSource.getActive());
            CHECK_FALSE(audioService->calledPlaySfx);
            CHECK_FALSE(audioService->calledStopSfx);
            CHECK_FALSE(audioService->calledPreloadSfx);
        }
        SUBCASE("Music"){
            musicSource.setActive(false);
            musicSource.onStart();
            musicSource.play();
            musicSource.stop();
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