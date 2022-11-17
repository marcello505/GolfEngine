#include <SDL.h>
#include <memory>
#include <iostream>
#include <vector>
#include "Services/SDLAudioService.h"

bool running = true;
bool paused = false;
std::vector<int> channelVolumes {10, 10, 10, 10};
float globalVolume = 10;
void getInput(SDLAudioService *audioService);

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;

    std::unique_ptr<SDLAudioService>_audioService(new SDLAudioService(3));
    _audioService->setVolumeChannel(0, channelVolumes[0]);
    _audioService->setVolumeChannel(1, channelVolumes[1]);
    _audioService->setVolumeChannel(2, channelVolumes[2]);
    _audioService->setVolumeChannel(3, channelVolumes[3]);
    _audioService->preloadAudio("D:/GitHub/SPC-Project/validation/US12_AudioService/resources/gun-cocking-01.wav");
    _audioService->preloadAudio("D:/GitHub/SPC-Project/validation/US12_AudioService/resources/short-shot.wav");
    _audioService->preloadAudio("D:/GitHub/SPC-Project/validation/US12_AudioService/resources/grenade.mp3");
    _audioService->preloadAudio("D:/GitHub/SPC-Project/validation/US12_AudioService/resources/mgs-theme.mp3");
    _audioService->playOnChannel(0, "D:/GitHub/SPC-Project/validation/US12_AudioService/resources/mgs-theme.mp3");

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
    SDL_DestroyWindow(window);
    _audioService->clearAudio();
    return 0;
}

void getInput(SDLAudioService *audioService) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            running = false;
        }
        else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_LEFT){

                audioService->playOnChannel(1, "D:/GitHub/SPC-Project/validation/US12_AudioService/"
                                                "resources/gun-cocking-01.wav");
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){
                audioService->playOnChannel(2, "D:/GitHub/SPC-Project/validation/US12_AudioService/"
                                               "resources/short-shot.wav");
            }
            else if(e.key.keysym.sym == SDLK_UP){
                audioService->playOnChannel(3, "D:/GitHub/SPC-Project/validation/US12_AudioService/"
                                               "resources/grenade.mp3");
            }
            else if(e.key.keysym.sym == SDLK_DOWN){
                paused = !paused;
                if(paused)
                {
                    audioService->pauseAudio(0);
                    continue;
                }
                audioService->resumeAudio(0);
            }
            else if(e.key.keysym.sym == SDLK_KP_ENTER){
                audioService->haltAudio(0);
            }
            else if(e.key.keysym.sym == SDLK_LEFTBRACKET){
                channelVolumes[2] -= 1;
                audioService->setVolumeChannel(2,  channelVolumes[2]);
            }
            else if(e.key.keysym.sym == SDLK_RIGHTBRACKET){
                channelVolumes[2] += 1;
                audioService->setVolumeChannel(2,  channelVolumes[2]);
            }
            else if(e.key.keysym.sym == SDLK_BACKSLASH){
                globalVolume -= 1;
                audioService->setGlobalVolume(globalVolume);
            }
            else if(e.key.keysym.sym == SDLK_SLASH){
                globalVolume += 1;
                audioService->setGlobalVolume(globalVolume);
            }
            else if(e.key.keysym.sym == SDLK_KP_3){
                audioService->playOnChannel(0, "D:/GitHub/SPC-Project/validation/US12_AudioService/resources/mgs-theme.mp3");
            }
        }
    }
}

