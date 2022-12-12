#include <doctest.h>

#include "Utilities/IO.h"

TEST_SUITE("IO"){
    TEST_CASE("Test"){

        CHECK_FALSE(GolfEngine::Utilities::IO::resourceFileExists("randomFile"));
    }
}