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
const char* gunCockingPath = R"(..\..\..\validation\US12_AudioService\resources\gun-cocking-01.wav)";
const char* shortShotPath = R"(..\..\..\validation\US12_AudioService\resources\short-shot.wav)";
const char* grenadePath = R"(..\..\..\validation\US12_AudioService\resources\grenade.mp3)";
const char* mgsThemePath = R"(..\..\..\validation\US12_AudioService\resources\mgs-theme.mp3)";

int main(int argc, char* argv[])
{
    // instantiate sdl window for catching events
    SDL_Window* window = nullptr;

    // instantiate audioservice
    std::unique_ptr<SDLAudioService>_audioService(new SDLAudioService(3));

    //setup audio sources
    _audioService->preloadAudio(gunCockingPath);
    _audioService->preloadAudio(shortShotPath);
    _audioService->preloadAudio(grenadePath);
    _audioService->preloadAudio(mgsThemePath);

    //play music on start
    _audioService->playOnChannel(0, mgsThemePath, 80);

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
    _audioService->clearAudio();
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
                audioService->playOnChannel(1, gunCockingPath, 100);
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){ // for playing a sound
                audioService->playOnChannel(2, shortShotPath, 100);
            }
            else if(e.key.keysym.sym == SDLK_UP){ //for playing a sound
                audioService->playOnChannel(3, grenadePath, 100);
            }
            else if(e.key.keysym.sym == SDLK_DOWN){ // for toggling pause / resuming of audio
                paused = !paused;
                if(paused)
                {
                    audioService->pauseAudio(0);
                    continue;
                }
                audioService->resumeAudio(0);
            }
            else if(e.key.keysym.sym == SDLK_KP_ENTER){ // for halting audio
                audioService->haltAudio(0);
            }
            else if(e.key.keysym.sym == SDLK_LEFTBRACKET){ // for setting volume of channel down
                channelVolumes[2] -= 1;
                audioService->setVolumeChannel(2,  channelVolumes[2]);
            }
            else if(e.key.keysym.sym == SDLK_RIGHTBRACKET){ // for setting volume of channel up
                channelVolumes[2] += 1;
                audioService->setVolumeChannel(2, channelVolumes[2]);
            }
            else if(e.key.keysym.sym == SDLK_BACKSLASH){ // for setting global volume down
                globalVolume -= 1;
                audioService->setGlobalVolume(globalVolume);
            }
            else if(e.key.keysym.sym == SDLK_SLASH){ // for setting global volume up
                globalVolume += 1;
                audioService->setGlobalVolume(globalVolume);
            }
            else if(e.key.keysym.sym == SDLK_KP_3){ // for playing sound after halt
                audioService->playOnChannel(0, mgsThemePath, 80);
            }
        }
    }
}

