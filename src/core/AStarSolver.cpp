
#include "AStarSolver.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <queue>
#include <vector>

PathfindingResult AStarSolver::solve(const MazeMap& maze) {
    PathfindingResult result;

    // 1. 获取迷宫的行数、列数和起点、终点
    const int rows = maze.rows();
    const int cols = maze.cols();

    const int startRow = maze.startRow();
    const int startCol = maze.startCol();

    const int goalRow = maze.goalRow();
    const int goalCol = maze.goalCol();

    // 2. 检查起点和终点是否合法
    if (!maze.inBound(startRow, startCol) ||
        !maze.inBound(goalRow, goalCol)) {
        return result;
    }

    if (maze.at(startRow, startCol) == CellType::Wall ||
        maze.at(goalRow, goalCol) == CellType::Wall) {
        return result;
    }

    // 3. 定义一个节点
    struct Node {
        int row;
        int col;
        int g;
        int f;
    };

    // 4. 小顶堆：优先取 f 值最小的节点
    struct Compare {
        bool operator()(const Node& a, const Node& b) const {
            return a.f > b.f;
        }
    };

    std::priority_queue<Node, std::vector<Node>, Compare> openList;

    // 5. 初始化 gScore 和 parent
    const int INF = std::numeric_limits<int>::max();

    std::vector<std::vector<int>> gScore(
        rows, std::vector<int>(cols, INF)
    );

    std::vector<std::vector<std::pair<int, int>>> parent(
        rows,
        std::vector<std::pair<int, int>>(cols, { -1, -1 })
    );

    // 6. 定义 Manhattan 距离
    auto heuristic = [&](int row, int col) {
        return std::abs(row - goalRow) + std::abs(col - goalCol);
        };

    // 7. 将起点加入 Open List
    gScore[startRow][startCol] = 0;

    openList.push({
        startRow,
        startCol,
        0,
        heuristic(startRow, startCol)
        });

    result.steps.push_back({
        startRow,
        startCol,
        SearchState::Open
        });

    // 8. 四个移动方向：上、下、左、右
    const std::array<std::pair<int, int>, 4> directions = { {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    } };

    // 9. 开始 A* 搜索
    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        const int r = current.row;
        const int c = current.col;

        // 跳过已经过期的节点
        if (current.g != gScore[r][c]) {
            continue;
        }

        // 当前节点从 Open 变为 Closed
        result.steps.push_back({
            r,
            c,
            SearchState::Closed
            });

        // 10. 如果到达终点，开始还原路径
        if (r == goalRow && c == goalCol) {
            std::vector<std::pair<int, int>> reversedPath;

            int pathRow = goalRow;
            int pathCol = goalCol;

            while (pathRow != startRow || pathCol != startCol) {
                reversedPath.emplace_back(pathRow, pathCol);

                auto previous = parent[pathRow][pathCol];

                if (previous.first == -1) {
                    return result;
                }

                pathRow = previous.first;
                pathCol = previous.second;
            }

            reversedPath.emplace_back(startRow, startCol);

            std::reverse(reversedPath.begin(), reversedPath.end());

            result.path = std::move(reversedPath);
            result.success = true;

            // 记录最终路径状态
            for (const auto& [row, col] : result.path) {
                result.steps.push_back({
                    row,
                    col,
                    SearchState::Path
                    });
            }

            return result;
        }

        // 11. 遍历当前节点的四个相邻节点
        for (const auto& [dr, dc] : directions) {
            const int nr = r + dr;
            const int nc = c + dc;

            // 检查是否越界
            if (!maze.inBound(nr, nc)) {
                continue;
            }

            // 检查是否为墙壁
            if (maze.at(nr, nc) == CellType::Wall) {
                continue;
            }

            // 计算经过当前节点到达邻居的代价
            const int tentativeG = gScore[r][c] + 1;

            // 只有找到更短的路径才更新
            if (tentativeG < gScore[nr][nc]) {
                gScore[nr][nc] = tentativeG;

                parent[nr][nc] = { r, c };

                const int f = tentativeG + heuristic(nr, nc);

                openList.push({
                    nr,
                    nc,
                    tentativeG,
                    f
                    });

                // 记录节点进入 Open List
                result.steps.push_back({
                    nr,
                    nc,
                    SearchState::Open
                    });
            }
        }
    }

    // 12. Open List 为空，说明不存在可行路径
    result.success = false;

    return result;
}
