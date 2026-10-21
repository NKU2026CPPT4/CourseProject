#pragma once

#include <vector>
#include <utility>
#include "core/MazeMap.h"

/**
 * @brief Represents a single step action during generation.
 */
struct MazeStep {
    int row;
    int col;
    CellType type;
};

/**
 * @brief The result of a maze generation process, including the final map and the animation steps.
 */
struct GenerationResult {
    MazeMap maze;
    std::vector<MazeStep> steps;
};

/**
 * @brief Represents the state of a node during pathfinding.
 */
enum class SearchState {
    Open,
    Closed,
    Path
};

/**
 * @brief Represents a step finding takes during pathfinding.
 */
struct SearchStep {
    int row;
    int col;
    SearchState state;
};

/**
 * @brief Represent the steps in a pathfinding process.
 */
struct PathfindingResult {
    bool success = false;
    std::vector<SearchStep> steps;
    std::vector<std::pair<int, int>> path;
};