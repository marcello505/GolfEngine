#include <doctest.h>
#include <SDL_mixer.h>


TEST_CASE("SDL2_mixer version get version returns something"){
    auto version = Mix_Linked_Version();

    CHECK_NE(version, nullptr);
}