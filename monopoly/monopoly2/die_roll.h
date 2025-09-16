//
// Created by Phil Nash on 16/09/2025.
//

#ifndef MONOPOLY2_DIE_ROLL_H
#define MONOPOLY2_DIE_ROLL_H

#include <random>

inline uint32_t die_roll(int from, int to) {
    static std::mt19937 rng((std::random_device()()));
    std::uniform_int_distribution<> rnd( from, to );
    return rnd(rng);
}

#endif // MONOPOLY2_DIE_ROLL_H
