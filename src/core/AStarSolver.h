#pragma once
#include "core/PathFinder.h"

class AStarSolver : public PathFinder {
public:
    PathfindingResult solve(const MazeMap& maze) override; 
};