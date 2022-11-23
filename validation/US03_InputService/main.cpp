#include <SDL.h>
#include <memory>
#include <iostream>
#include "Services/SDLInputService.h"

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    std::unique_ptr<SDLInputService>inputService(new SDLInputService());


    auto _actionMap = ActionMap::getActionMap();

    // creating actions
    _actionMap->addAction("Reload");
    _actionMap->addAction("WalkUp");
    _actionMap->addAction("WalkDown");
    _actionMap->addAction("WalkLeft");
    _actionMap->addAction("WalkRight");
    _actionMap->addAction("ThrowGrenade");
    _actionMap->addAction("Shoot");
    _actionMap->addAction("Aim");

    // binding actions to keys
    _actionMap->addInputKeyToAction("Reload", Key_R);
    _actionMap->addInputKeyToAction("WalkUp", Key_W);
    _actionMap->addInputKeyToAction("WalkDown", Key_S);
    _actionMap->addInputKeyToAction("WalkLeft", Key_A);
    _actionMap->addInputKeyToAction("WalkRight", Key_D);
    _actionMap->addInputKeyToAction("ThrowGrenade", Key_Q);
    _actionMap->addInputKeyToAction("Shoot", Mouse_Left);
    _actionMap->addInputKeyToAction("Aim", Mouse_Right);

    // initialize video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    // create SDL window
    window = SDL_CreateWindow("C++ SDL2 Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);


    // call input handle on loop
    while (!(inputService->hasRecievedQuitSignal()))
    {
        inputService->handleInputs();
    }

    // destroy window
    SDL_DestroyWindow(window);

    return 0;
}