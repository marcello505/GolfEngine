//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_COLOR_H
#define GOLFENGINE_COLOR_H


#include <cstddef>
#include <cstdint>

namespace GolfEngine::Scene {
    struct Color {
        std::uint8_t r8;
        std::uint8_t g8;
        std::uint8_t b8;
        std::uint8_t a;

        explicit Color(std::uint8_t R8 = 255, std::uint8_t G8 = 255, std::uint8_t B8 = 255, std::uint8_t A = 255) : r8{
                R8}, g8{G8}, b8{B8}, a{A} {}
    };
}

#endif //GOLFENGINE_COLOR_H
