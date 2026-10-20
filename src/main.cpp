/**
 * NOTE : This is currently a test file for maze generation, MODIFY BEFORE RELEASING!
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#include "core/MazeMap.h"
#include "core/DFSGenerator.h"

// 用 BFS 算法测试起点到终点是否连通
static bool isConnected(const MazeMap& maze) {
    const int rows = maze.rows();
    const int cols = maze.cols();

    // 记录是否访问过
    std::vector visited(rows, std::vector(cols, false));
    std::queue<std::pair<int, int>> q;

    // 压入起点
    q.emplace(maze.startRow(), maze.startCol());
    visited[maze.startRow()][maze.startCol()] = true;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        // 如果到达终点，返回 true
        if (r == maze.goalRow() && c == maze.goalCol()) {
            return true;
        }

        // 向上下左右四个方向探索
        for (int i = 0; i < 4; ++i) {
            constexpr int dc[] = {0, 0, -1, 1};
            constexpr int dr[] = {-1, 1, 0, 0};
            int nr = r + dr[i];
            // ReSharper disable once CppTooWideScopeInitStatement
            int nc = c + dc[i];

            // 如果在边界内、不是墙、且没走过，就加入队列
            if (maze.inBound(nr, nc) &&
                maze.at(nr, nc) != CellType::Wall &&
                !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.emplace(nr, nc);
            }
        }
    }
    return false; // 队列空了还没找到，说明不连通
}

int main() {
    constexpr int rows = 25;
    constexpr int cols = 25;

    std::cout << "Starting connectivity test for seeds 0 to 4...\n\n";

    // 循环测试前 15 个种子，确保算法绝对稳定
    for (unsigned int seed = 0; seed < 15; ++seed) {
        DFSGenerator generator(seed);
        MazeMap maze = generator.generate(rows, cols);

        std::cout << "Seed " << seed << ": ";
        if (isConnected(maze)) {
            std::cout << "CONNECTED!\n";
        } else {
            std::cout << "FAILED (Blocked)!\n";
        }
    }

    // 单独生成一个种子为 42 的迷宫并打印出来看效果
    std::cout << "\n========================================\n";
    std::cout << "Visual output for Seed 43:\n";
    std::cout << "========================================\n";

    DFSGenerator visualGen(43);
    const MazeMap finalMaze = visualGen.generate(rows, cols);
    finalMaze.print();

    return 0;
}