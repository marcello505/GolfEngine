#include <random>

#include "Random.h"

namespace GolfEngine::Utilities {
    //Initialize static Random Engine
    std::default_random_engine Random::randomEngine = std::default_random_engine {std::random_device()()};

    void Random::setSeed(std::default_random_engine::result_type s) {
        randomEngine.seed(s);
    }

    void Random::setRandomSeed() {
        randomEngine.seed(std::random_device()());
    }

    bool Random::getBool() {
        std::bernoulli_distribution dist {};
        return dist(randomEngine);
    }

} // Random
