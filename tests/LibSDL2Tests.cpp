#include <doctest.h>
#include <SDL.h>

TEST_CASE("SDL2 version get version returns something"){
    SDL_version version {};
    SDL_GetVersion(&version);

    CHECK_EQ(version.major, 2);
}
