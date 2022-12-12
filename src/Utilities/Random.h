//
// Created by marcello on 12-12-22.
//

#ifndef GOLFENGINE_RANDOM_H
#define GOLFENGINE_RANDOM_H

#include <random>

namespace GolfEngine::Utilities {
    class Random{
    public:
        // ========
        // Getters

        /// Generates a randomly generated integer in range using uniform_int_distribution
        /// \tparam T an integer type
        /// \param min minumum of distribution
        /// \param max maximum of distribution
        /// \return A randomly generated integer between min and max
        template<class T> static T getIntRange(T min, T max){
            std::uniform_int_distribution<T> dist {min, max};
            return dist(randomEngine);
        }
        /// Generates a randomly generated real number in range using uniform_real_distribution
        /// \tparam T a real type
        /// \param min minimum of distribution
        /// \param max maximum of distribution
        /// \return A randomly generated real number between min and max
        template<class T> static T getRealRange(T min, T max){
            std::uniform_real_distribution<T> dist {min, max};
            return dist(randomEngine);
        }
        /// Generates a random boolean using the bernoulli_distribution
        /// \return a randomly generated boolean
        static bool getBool();

        // =========
        // Setters

        /// Set the seed of the RandomEngine to the one given, used mainly by replays to make the randomness consistent.
        /// \param s the new seed.
        static void setSeed(std::default_random_engine::result_type s);
        /// Set the seed of the RandomEngine to a random one by using the RandomDevice class.
        static void setRandomSeed();
    private:
        static std::default_random_engine randomEngine;
    };

}

#endif //GOLFENGINE_RANDOM_H
