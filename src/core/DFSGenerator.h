#pragma once
#include "core/MazeMap.h"
#include "core/Step.h"
#include <random>


/**
 * @brief The maze generator class using the Depth-First Search (DFS) algorithm.
 *
 * This class generates a maze using the randomized DFS (backtracking) approach.
 * It guarantees a connected maze with a perfect tree structure
 * (no isolated regions or loops).
 */
class DFSGenerator {
public:
    /**
     * @brief Constructs a DFS maze generator with a specific random seed.
     * @param seed unsigned int The random seed.
     * @note Passing the same seed generates the exact same maze, which is useful for reproducible testing.
     */
    explicit DFSGenerator(unsigned int seed);

    /**
     * @brief Generates a fully connected maze of the specified dimensions.
     *
     * The generated maze has a closed outer boundary wall.
     * The start point is set at (1, 1), and the goal point is set at (rows-2, cols-2).
     * The algorithm works by moving 2 steps at a time and carving out the wall in between,
     * ensuring the maze maintains a proper wall thickness.
     *
     * @param rows The total number of rows (odd numbers are highly recommended).
     * @param cols The total number of columns (odd numbers are highly recommended).
     * @return MazeMap The generated maze data object.
     */
    MazeMap generate(int rows, int cols);

    /**
     * @brief Generates a maze and records every step for visualization.
     * @param rows The total number of rows.
     * @param cols The total number of columns.
     * @return GenerationResult Contains the final maze and the step-by-step animation data.
     */
    GenerationResult generateWithSteps(int rows, int cols);


private:
    std::mt19937 rng_; /////< Mersenne Twister random generator.
};