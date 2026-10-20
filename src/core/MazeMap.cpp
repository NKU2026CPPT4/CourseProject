#include "core/MazeMap.h"

MazeMap::MazeMap(const int rows, const int cols) : rows_(rows), cols_(cols) {
    grid_ = std::vector<std::vector<CellType>>(rows, std::vector<CellType>(cols, CellType::Wall));
}

int MazeMap::rows() const {
    return rows_;
}

int MazeMap::cols() const {
    return cols_;
}

bool MazeMap::inBound(const int row, const int col) const {
    return row >= 0 && row < rows_ && col >= 0 && col < cols_;
}

CellType MazeMap::at(const int row, const int col) const {
    if (inBound(row, col)) {
        return grid_[row][col];
    }
    return CellType::Wall;
}

void MazeMap::set(const int row, const int col, const CellType cell) {
    if (inBound(row, col)) {
        grid_[row][col] = cell;
    }
}

void MazeMap::setStart(const int row, const int col) {
    if (inBound(row, col)) {
        startRow_ = row;
        startCol_ = col;
        grid_[row][col] = CellType::Start;
    }
}

void MazeMap::setGoal(const int row, const int col) {
    if (inBound(row, col)) {
        goalRow_ = row;
        goalCol_ = col;
        grid_[row][col] = CellType::Goal;
    }
}

void MazeMap::print(std::ostream& os) const {
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            if (r == startRow_ && c == startCol_) {
                os << "S ";
            } else if (r == goalRow_ && c == goalCol_) {
                os << "G ";
            } else if (grid_[r][c] == CellType::Wall) {
                os << "##";
            } else {
                os << "  ";
            }
        }
        os << "\n";
    }
}