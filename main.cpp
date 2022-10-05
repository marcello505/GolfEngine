#include <iostream>
#include <SDL.h>

int main()
{
    auto d = SDL_GetTicks();


    std::cout << d << std::endl;
    return 0;
}
