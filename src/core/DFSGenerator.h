#pragma once
#include "core/Generator.h"


/**
 * @brief The maze generator class using the Depth-First Search (DFS) algorithm.
 *
 * This class generates a maze using the randomized DFS (backtracking) approach.
 * It guarantees a connected maze with a perfect tree structure
 * (no isolated regions or loops).
 */
class DFSGenerator : public Generator {
public:
    using Generator::Generator;

    /**
     * @brief Generates a maze and records every step for visualization.
     * @param rows The total number of rows.
     * @param cols The total number of columns.
     * @return GenerationResult Contains the final maze and the step-by-step animation data.
     */
    GenerationResult generateWithSteps(int rows, int cols) override;
};
