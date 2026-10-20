#pragma once

#include <vector>
#include <iostream>

enum class CellType {
    Wall,
    Passage,
    Start,
    Goal
};

class MazeMap {
public:
    MazeMap(int rows, int cols);

    [[nodiscard]] int rows() const;
    [[nodiscard]] int cols() const;

    // 注意：这里拼写是 inBound，实现里会保持一致
    [[nodiscard]] bool inBound(int row, int col) const;

    [[nodiscard]] CellType at(int row, int col) const;

    void set(int row, int col, CellType cell);

    void setStart(int row, int col);
    void setGoal(int row, int col);

    // 补充获取起终点坐标的方法，方便后续 A* 算法调用
    [[nodiscard]] int startRow() const { return startRow_; }
    [[nodiscard]] int startCol() const { return startCol_; }
    [[nodiscard]] int goalRow() const { return goalRow_; }
    [[nodiscard]] int goalCol() const { return goalCol_; }

    void print(std::ostream& os = std::cout) const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<CellType>> grid_;

    // 初始化默认值为 -1，表示尚未设置起终点
    int startRow_ = -1;
    int startCol_ = -1;
    int goalRow_ = -1;
    int goalCol_ = -1;
};