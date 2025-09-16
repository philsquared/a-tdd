//
// Created by Phil Nash on 16/09/2025.
//

#ifndef MONOPOLY2_RANDOM_NUMBER_H
#define MONOPOLY2_RANDOM_NUMBER_H

#include <random>

inline uint32_t random_number(int from, int to) {
    static std::mt19937 rng((std::random_device()()));
    std::uniform_int_distribution<> rnd( from, to );
    return rnd(rng);
}

#endif // MONOPOLY2_RANDOM_NUMBER_H
