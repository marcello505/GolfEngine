#include <doctest.h>

#include "Utilities/Random.h"

TEST_SUITE("Random"){
    TEST_CASE("setSeed() always results in the same number"){
        //Arrange
        auto seed = GolfEngine::Utilities::Random::setRandomSeed();

        //Act
        auto firstResult = GolfEngine::Utilities::Random::getIntRange(0, 100);
        auto seccondResult = GolfEngine::Utilities::Random::getIntRange(0, 100);

        GolfEngine::Utilities::Random::setSeed(seed);
        auto thirdResult = GolfEngine::Utilities::Random::getIntRange(0, 100);

        //Assert
        CHECK_NE(firstResult, seccondResult);
        CHECK_EQ(firstResult, thirdResult);
    }
}