#pragma once
#include "core/MazeMap.h"
#include <random>

class RecursiveDivisionGenerator {
public:
    explicit RecursiveDivisionGenerator(unsigned int seed);

    MazeMap generate(int rows, int cols);
};