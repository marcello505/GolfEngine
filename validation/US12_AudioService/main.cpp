#include <SDL.h>
#include <memory>
#include <iostream>
#include <vector>
#include "Services/SDLAudioService.h"
#include <filesystem>

bool running = true; // outer loop input
bool paused = false; // for pause/resume toggle
std::vector<float> channelVolumes {50, 50, 50, 50}; // storage for channel volumes
float globalVolume = 80; // global volume
void getInput(SDLAudioService *audioService);

// asset paths
//TODO opus support wordt niet standaard ondersteund door SDL2_Mixer, dit verist extra build opties. Verwijder Opus files, of maak een windows build waar dit wel wordt ondersteund.
std::string gunCockingPath = "resources/gun-cocking-01.opus";
std::string shortShotPath = "resources/short-shot.ogg";
std::string grenadePath = "resources/grenade.mp3";
std::string mgsThemePath = "resources/mgs-theme.flac";

int main(int argc, char* argv[])
{
    // instantiate sdl window for catching events
    SDL_Window* window = nullptr;

    // instantiate audioservice
    std::unique_ptr<SDLAudioService> _audioService = std::make_unique<SDLAudioService>();

    //setup audio sources
    _audioService->preloadSfx(gunCockingPath);
    _audioService->preloadSfx(shortShotPath);
    _audioService->preloadSfx(grenadePath);
    _audioService->preloadMusic(mgsThemePath);

    //play music on start
    _audioService->playMusic(mgsThemePath, 0.5f, true);

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
        getInput(_audioService.get());
    }

    //cleanup
    SDL_DestroyWindow(window);
    _audioService->clearCache();
    return 0;
}

void getInput(SDLAudioService *audioService) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) { //catch input events
        if(e.type == SDL_QUIT) { // for closing window
            running = false;
        }
        else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_LEFT){ // for playing a sound
                audioService->playSfx(gunCockingPath, 1.0f);
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){ // for playing a sound
//                audioService->playSfx(shortShotPath, 1.0f);
                audioService->playSfx(grenadePath, 0.5f);
            }
            else if(e.key.keysym.sym == SDLK_UP){ //for playing a sound
                audioService->playSfx(grenadePath, 1.0f);
            }
            else if(e.key.keysym.sym == SDLK_DOWN){ // for toggling pause / resuming of audio
                audioService->toggleMusic();
            }
            else if(e.key.keysym.sym == SDLK_MINUS){ // for setting master volume down
                audioService->setMasterVolume(audioService->getMasterVolume() - 0.1f);
            }
            else if(e.key.keysym.sym == SDLK_EQUALS){ // for setting master volume up
                audioService->setMasterVolume(audioService->getMasterVolume() + 0.1f);
            }
            else if(e.key.keysym.sym == SDLK_9){ // for setting music volume down
                audioService->setMusicVolume(audioService->getMusicVolume() - 0.1f);
            }
            else if(e.key.keysym.sym == SDLK_0){ // for setting music volume down
                audioService->setMusicVolume(audioService->getMusicVolume() + 0.1f);
            }
            else if(e.key.keysym.sym == SDLK_7){ // for setting music volume down
                audioService->setSfxVolume(audioService->getSfxVolume() - 0.1f);
            }
            else if(e.key.keysym.sym == SDLK_8){ // for setting music volume down
                audioService->setSfxVolume(audioService->getSfxVolume() + 0.1f);
            }
            else if(e.key.keysym.sym == SDLK_RETURN){ // for playing sound after halt
                audioService->playMusic(mgsThemePath, 1.0f, false);
            }
            else if(e.key.keysym.sym == SDLK_BACKSPACE){ // for halting audio
                audioService->stopMusic();
            }
        }
    }
}

