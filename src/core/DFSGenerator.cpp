#include "core/DFSGenerator.h"
#include <vector>
#include <algorithm>

DFSGenerator::DFSGenerator(const unsigned int seed) : rng_(seed) {
}

MazeMap DFSGenerator::generate(const int rows, const int cols) {
    MazeMap maze(rows, cols);

    // Algorithm: dfs
    std::vector<std::pair<int, int>> trace;
    trace.emplace_back(1, 1);
    maze.set(1, 1, CellType::Passage);

    // Delta of position in four directions
    static constexpr int dr[] = {-2, 2, 0, 0};
    static constexpr int dc[] = {0, 0, -2, 2};

    while (!trace.empty()) {
        auto [r,c] = trace.back(); // Current coordinate

        std::vector<int> dirs = {0, 1, 2,3 };
        std::shuffle(dirs.begin(), dirs.end(), rng_);

        bool moved = false;
        for (const auto d : dirs) {
            const int nr = r + dr[d];
            // ReSharper disable once CppTooWideScopeInitStatement
            const int nc = c + dc[d]; // (nr, nc) is the candidate coordinate.

            // Check if the candidate is inBound and unvisited (remain CellType:Wall)
            if (maze.inInnerBound(nr, nc) && maze.at(nr, nc) == CellType::Wall) {
                maze.set(r + dr[d] / 2, c + dc[d] / 2, CellType::Passage);
                maze.set(nr, nc, CellType::Passage);

                trace.emplace_back(nr, nc);
                moved = true;
                break;

            }
        }

        if (!moved) {
            trace.pop_back();
        }
    }

    maze.setStart(1, 1);
    maze.setGoal(rows - 2, cols - 2);

    return maze;
}