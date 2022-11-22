#include <doctest.h>
#include <SDL_ttf.h>


TEST_CASE("SDL2_ttf version get version returns something"){
    auto version = TTF_Linked_Version();


    CHECK_NE(version, nullptr);
}