#pragma once
#include "core/PathFinder.h"

/**
 * @brief Implements A* pathfinding algorithm
 */
class AStarSolver : public PathFinder {
public:
    /**
     * @brief Solves the maze via A* algorithm
     * @param maze The reference to the maze map.
     * @return PathfindingResult The result.
     */
    PathfindingResult solve(const MazeMap &maze) override;
};
