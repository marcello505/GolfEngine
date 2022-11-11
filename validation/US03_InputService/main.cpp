#include <SDL.h>
#include <memory>
#include <iostream>
#include "Services/SDLInputService.h"
#include "Input/ActionMap.h"
#include <SDL_image.h>

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    std::unique_ptr<ActionMap> _actionMap = std::make_unique<ActionMap>();

    _actionMap->addAction("Reload");
    _actionMap->addAction("WalkUp");
    _actionMap->addAction("WalkDown");
    _actionMap->addAction("WalkLeft");
    _actionMap->addAction("WalkRight");
    _actionMap->addAction("ThrowGrenade");
    _actionMap->addAction("Shoot");
    _actionMap->addAction("Aim");

    _actionMap->addInputKeyToAction("Reload", Key_R);
    _actionMap->addInputKeyToAction("WalkUp", Key_W);
    _actionMap->addInputKeyToAction("WalkDown", Key_S);
    _actionMap->addInputKeyToAction("WalkLeft", Key_A);
    _actionMap->addInputKeyToAction("WalkRight", Key_D);
    _actionMap->addInputKeyToAction("ThrowGrenade", Key_Q);
    _actionMap->addInputKeyToAction("Shoot", Mouse_Left);
    _actionMap->addInputKeyToAction("Aim", Mouse_Right);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("C++ SDL2 Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);


    std::unique_ptr<SDLInputService>inputService(new SDLInputService(_actionMap.get()));
    inputService->handleInputs();

    SDL_DestroyWindow(window);

    return 0;
}