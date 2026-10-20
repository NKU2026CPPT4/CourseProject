#include "core/RecursiveDivision.h"

RecursiveDivisionGenerator::RecursiveDivisionGenerator(const unsigned int seed) : rng_(seed) {}

MazeMap RecursiveDivisionGenerator::generate(const int rows, const int cols) {
    (void) rng_;

    MazeMap maze(rows, cols);

    // Fake logic: set passage to all inside cells.
    for (int r = 1; r < rows - 1; r++) {
        for (int c = 1; c < cols - 1; c++) {
            maze.set(r, c, CellType::Passage);
        }
    }

    maze.setStart(1, 1);
    maze.setGoal(rows - 2, cols - 2);

    return maze;
}

void RecursiveDivisionGenerator::divide(MazeMap& maze, int top, int bottom, int left, int right) {
    int wallRow = std::uniform_int_distribution<int>(top + 1, bottom - 1)(rng_);
}