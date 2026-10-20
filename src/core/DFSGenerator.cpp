#include "core/DFSGenerator.h"
#include <vector>
#include <algorithm>

DFSGenerator::DFSGenerator(const unsigned int seed) : rng_(seed) {
}

GenerationResult DFSGenerator::generateWithSteps(const int rows, const int cols) {
    MazeMap maze(rows, cols);
    std::vector<MazeStep> steps;

    // Algorithm: dfs
    std::vector<std::pair<int, int>> trace;
    trace.emplace_back(1, 1);
    maze.set(1, 1, CellType::Passage);

    // Record the first step
    steps.push_back({.row = 1, .col = 1, .type = CellType::Passage});

    // Delta of position in four directions
    static constexpr int dr[] = {-2, 2, 0, 0};
    static constexpr int dc[] = {0, 0, -2, 2};

    while (!trace.empty()) {
        auto [r,c] = trace.back(); // Current coordinate

        std::vector<int> dirs = {0, 1, 2, 3};
        std::shuffle(dirs.begin(), dirs.end(), rng_);

        bool moved = false;
        for (const auto d : dirs) {
            const int nr = r + dr[d];
            // ReSharper disable once CppTooWideScopeInitStatement
            const int nc = c + dc[d]; // (nr, nc) is the candidate coordinate.

            // Check if the candidate is inBound and unvisited (remain CellType:Wall)
            if (maze.inInnerBound(nr, nc) && maze.at(nr, nc) == CellType::Wall) {
                const int mid_r = r + dr[d] / 2;
                const int mid_c = c + dc[d] / 2;

                maze.set(mid_r, mid_c, CellType::Passage);
                steps.push_back({mid_r, mid_c, CellType::Passage});

                maze.set(nr, nc, CellType::Passage);
                steps.push_back({nr, nc, CellType::Passage});

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
    steps.push_back({.row = 1, .col = 1, .type = CellType::Start});
    maze.setGoal(rows - 2, cols - 2);
    steps.push_back({.row = rows - 2, .col = cols - 2, .type = CellType::Goal});

    return {maze, steps};
}

MazeMap DFSGenerator::generate(const int rows, const int cols) {
    return generateWithSteps(rows, cols).maze;
}