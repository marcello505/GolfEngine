#include <SDL.h>
#include <memory>
#include <iostream>
#include "Services/SDLInputService.h"
#include "Input/ActionMap.h"


int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    std::unique_ptr<ActionMap> _actionMap = std::make_unique<ActionMap>();

    _actionMap->addAction("Reload");
    _actionMap->addAction("Shoot");
    _actionMap->addAction("ThrowGrenade");
    _actionMap->addAction("Jump");

    _actionMap->addInputKeyToAction("Reload", Key_Left);
    _actionMap->addInputKeyToAction("Shoot", Key_Right);
    _actionMap->addInputKeyToAction("ThrowGrenade", Key_Up);
    _actionMap->addInputKeyToAction("Jump", Key_Up);


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("C++ SDL2 Window", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

    std::unique_ptr<SDLInputService>inputService(new SDLInputService(_actionMap.get()));
    inputService->handleInputs();

    SDL_DestroyWindow(window);

    return 0;
}