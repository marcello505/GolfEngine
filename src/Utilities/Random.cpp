#include <random>

#include "Random.h"

namespace GolfEngine::Utilities {
    //Initialize static Random Engine
    std::default_random_engine Random::randomEngine = std::default_random_engine {std::random_device()()};

    void Random::setSeed(std::default_random_engine::result_type s) {
        randomEngine.seed(s);
    }

    std::random_device::result_type Random::setRandomSeed() {
        auto seed = std::random_device()();
        randomEngine.seed(seed);
        return seed;
    }

    bool Random::getBool() {
        std::bernoulli_distribution dist {};
        return dist(randomEngine);
    }

} // Random
