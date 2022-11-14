#include <SDL.h>
#include <memory>
#include <iostream>
#include "Services/SDLAudioService.h"



int main(int argc, char* argv[])
{
    std::unique_ptr<SDLAudioService>_audioService(new SDLAudioService(3));
    _audioService->preloadAudio("D:/GitHub/SPC-Project/validation/US12_AudioService/resources/gun-cocking-01.wav");
    _audioService->preloadAudio("D:/GitHub/SPC-Project/validation/US12_AudioService/resources/short-shot.wav");
    _audioService->preloadAudio("D:/GitHub/SPC-Project/validation/US12_AudioService/resources/grenade.mp3");
    SDLAudioService service;
    std::cout << "finished";
    return 0;
}