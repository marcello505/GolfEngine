#include <doctest.h>
#include <SDL_image.h>

TEST_CASE("SDL2_image get version returns something"){
    auto version = IMG_Linked_Version();

    CHECK_NE(version, nullptr);
}