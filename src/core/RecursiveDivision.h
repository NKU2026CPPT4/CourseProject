#pragma once
#include "core/MazeMap.h"
#include <random>

class RecursiveDivisionGenerator {
public:
    explicit RecursiveDivisionGenerator(unsigned int seed);

    MazeMap generate(int rows, int cols);

private:
    std::mt19937 rng_;
    void divide(MazeMap& maze, int top, int bottom, int left, int right);
};