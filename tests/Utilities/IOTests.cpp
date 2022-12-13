#include <doctest.h>

#include "Utilities/IO.h"

TEST_SUITE("IO"){
    TEST_CASE("Test"){

        CHECK_THROWS(GolfEngine::Utilities::IO::resourceFileExists("randomFile"));
    }
}