#pragma once
#include "core/MazeMap.h"
#include "core/Step.h"

/**
 * @brief Universal (abstract) class for all pathfinding algorithms.
 */
class PathFinder {
public:
    virtual ~PathFinder() = default;

    /**
     * @brief Perform the pathfinding algorithm.
     * @param maze Map of the maze.
     * @return PathFindingResult The process of finding, in order to visualize.
     */
    virtual PathfindingResult solve(const MazeMap& maze) = 0;
};