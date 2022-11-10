#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <SDL.h>
#include <doctest.h>
/*#include <iostream>
#include "Services/SDLInputService.h"
#include "Input/ActionMap.h"


*//* main *//*
int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    ActionMap actionMap;

    actionMap.addAction("Reload");
    actionMap.addAction("Shoot");
    actionMap.addAction("ThrowGrenade");
    actionMap.addAction("Jump");

    actionMap.addInputKeyToAction("Reload", Key_Left);
    actionMap.addInputKeyToAction("Shoot", Key_Right);
    actionMap.addInputKeyToAction("ThrowGrenade", Key_Up);
    actionMap.addInputKeyToAction("Jump", Key_Up);


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("C++ SDL2 Window", 0, 2500, 640, 480, SDL_WINDOW_SHOWN);

    std::unique_ptr<SDLInputService>inputService(new SDLInputService(actionMap));
    inputService->handleInputs();

    SDL_DestroyWindow(window);

    exit(0);
}*/

