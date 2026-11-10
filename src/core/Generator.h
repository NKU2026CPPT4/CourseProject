#pragma once

#include "core/MazeMap.h"
#include "core/Step.h"
#include <random>


/**
 * @brief Universal (abstract) class for all generating algorithms.
 */
class Generator {
public:
    explicit Generator(const unsigned int seed) : rng_(seed) {};

    virtual ~Generator() = default;

    virtual GenerationResult generateWithSteps(int rows, int cols) = 0;

    virtual MazeMap generate(const int rows, const int cols) {
        return generateWithSteps(rows, cols).maze;
    }

protected:
    std::mt19937 rng_;
};