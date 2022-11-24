#include <SDL.h>
#include <memory>
#include <iostream>
#include <vector>
#include "Services/SDLAudioService.h"
#include <filesystem>
#include "Scene/Components/AudioSource.h"
#define GOLFENGINE_SINGLETON_PRIVATE
#include "Services/Singletons/AudioSingleton.h"

bool running = true; // outer loop input
bool paused = false; // for pause/resume toggle
std::vector<float> channelVolumes {50, 50, 50, 50}; // storage for channel volumes
float globalVolume = 80; // global volume

// asset paths
std::string gunCockingPath = "resources/gun-cocking-01.wav";
std::string shortShotPath = "resources/short-shot.ogg";
std::string grenadePath = "resources/grenade.mp3";
std::string mgsThemePath = "resources/mgs-theme.flac";

int main(int argc, char* argv[])
{
    // instantiate sdl window for catching events
    SDL_Window* window = nullptr;

    // instantiate audioservice
    GolfEngine::Services::Audio::setService(new SDLAudioService{});
    auto* _audioService = GolfEngine::Services::Audio::getService();

    _audioService->init();

    //setup audio sources
    GolfEngine::Scene::Components::AudioSource gunCockingSound {gunCockingPath, false};
    GolfEngine::Scene::Components::AudioSource shortShotSound {shortShotPath, false};
    GolfEngine::Scene::Components::AudioSource grenadeSound {grenadePath, false};
    GolfEngine::Scene::Components::AudioSource mgsThemeSound {mgsThemePath, true};

    gunCockingSound.onStart();
    shortShotSound.onStart();
    grenadeSound.onStart();
    mgsThemeSound.onStart();

    //play music on start
    mgsThemeSound.play(true);

    // initialize video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    // create SDL window
    window = SDL_CreateWindow("C++ SDL2 Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    while(running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) { //catch input events
            if(e.type == SDL_QUIT) { // for closing window
                running = false;
            }
            else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_LEFT){ // for playing a sound
                    if(e.key.keysym.mod & KMOD_SHIFT){
                        gunCockingSound.stop();
                    }
                    else{
                        gunCockingSound.play();
                    }
                }
                else if(e.key.keysym.sym == SDLK_RIGHT){ // for playing a sound
                    if(e.key.keysym.mod & KMOD_SHIFT){
                        shortShotSound.stop();
                    }
                    else{
                        shortShotSound.play();
                    }
                }
                else if(e.key.keysym.sym == SDLK_UP){ //for playing a sound
                    if(e.key.keysym.mod & KMOD_SHIFT){
                        grenadeSound.stop();
                    }
                    else{
                        grenadeSound.play();
                    }
                }
                else if(e.key.keysym.sym == SDLK_DOWN){ // for toggling pause / resuming of audio
                    _audioService->toggleMusic();
                }
                else if(e.key.keysym.sym == SDLK_MINUS){ // for setting master volume down
                    _audioService->setMasterVolume(_audioService->getMasterVolume() - 0.1f);
                }
                else if(e.key.keysym.sym == SDLK_EQUALS){ // for setting master volume up
                    _audioService->setMasterVolume(_audioService->getMasterVolume() + 0.1f);
                }
                else if(e.key.keysym.sym == SDLK_9){ // for setting music volume down
                    _audioService->setMusicVolume(_audioService->getMusicVolume() - 0.1f);
                }
                else if(e.key.keysym.sym == SDLK_0){ // for setting music volume down
                    _audioService->setMusicVolume(_audioService->getMusicVolume() + 0.1f);
                }
                else if(e.key.keysym.sym == SDLK_7){ // for setting music volume down
                    _audioService->setSfxVolume(_audioService->getSfxVolume() - 0.1f);
                }
                else if(e.key.keysym.sym == SDLK_8){ // for setting music volume down
                    _audioService->setSfxVolume(_audioService->getSfxVolume() + 0.1f);
                }
                else if(e.key.keysym.sym == SDLK_RETURN){ // for playing sound after halt
                    mgsThemeSound.play(true);
                }
                else if(e.key.keysym.sym == SDLK_BACKSPACE){ // for halting audio
                    mgsThemeSound.stop();
                }
            }
        }
    }

    //cleanup
    SDL_DestroyWindow(window);
    _audioService->free();

    return 0;
}

