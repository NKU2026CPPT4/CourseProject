#pragma once
#include <vector>
#include <iostream>

/**
 * @brief States of cells in a maze.
 */
enum class CellType {
    Wall, ///< A solid wall, which cannot be traversed.
    Passage, ///< An open passage which can be traversed.
    Start, ///< The starting point of a maze.
    Goal ///< The goal point of a maze.
};


/**
 * @brief The data model class for a maze map.
 *
 * Responsible for storing the 2D maze grid state, boundary dimensions,
 * and the coordinates of the start and goal points.
 * This does NOT contain maze generation of path finding algorithms.
 */
class MazeMap {
public:
    /**
     * @brief Constructs the maze with given dimensions.
     * @param rows The total number of the rows.
     * @param cols The total number of the columns.
     * @note All cells will be initialized to CellType::Wall.
     */
    MazeMap(int rows, int cols);

    /**
     * @brief Gets the number of rows in the maze.
     * @return int The number of rows.
     */
    [[nodiscard]] int rows() const;

    /**
     * @brief Gets the number of columns in the maze.
     * @return int The number of columns.
     */
    [[nodiscard]] int cols() const;

    /**
     * @brief Determines whether a specific coordinate does not exceed the physical boundaries.
     * @param row The row index of target point (0-based).
     * @param col The column index of target point (0-based).
     * @return true (in boundary) or false (otherwise).
     * @note This does NOT check whether the point is on the outer border wall.
     */
    [[nodiscard]] bool inBound(int row, int col) const;

    /**
     * @brief Determines whether a specific coordinate does not exceed the outer border wall.
     * @param row The row index of target point (0-based).
     * @param col The column index of target point (0-based).
     * @return true (in inner area) or false (otherwise).
     * @note This returns true ONLY if point is not located on the border.
     */
    [[nodiscard]] bool inInnerBound(int row, int col) const;

    /**
     * @brief Gets the cell type at the specified coordinates.
     * @param row The target row index.
     * @param col The target column index.
     * @return CellType The cell type (returns Wall if out of bounds).
     */
    [[nodiscard]] CellType at(int row, int col) const;

    /**
     * @brief Sets the cell type at the specified coordinates.
     * @param row The target row index.
     * @param col The target column index.
     * @param cell The cell type to set.
     */
    void set(int row, int col, CellType cell);

    /**
     * @brief Sets the starting point of the maze.
     * @param row The row index of the start point.
     * @param col The column index of the start point.
     * @note This updates both the grid state and the internal start coordinates.
     */
    void setStart(int row, int col);

    /**
     * @brief Sets the goal point of the maze.
     * @param row The row index of the goal point.
     * @param col The column index of the goal point.
     * @note This updates both the grid state and the internal goal coordinates.
     */
    void setGoal(int row, int col);

    /**
     * @brief Gets the row index of the start point.
     * @return int The start row index (-1 if not set).
     */
    [[nodiscard]] int startRow() const { return startRow_; }

    /**
     * @brief Gets the column index of the start point.
     * @return int The start column index (-1 if not set).
     */
    [[nodiscard]] int startCol() const { return startCol_; }

    /**
     * @brief Gets the row index of the goal point.
     * @return int The goal row index (-1 if not set).
     */
    [[nodiscard]] int goalRow() const { return goalRow_; }

    /**
     * @brief Gets the column index of the goal point.
     * @return int The goal column index (-1 if not set).
     */
    [[nodiscard]] int goalCol() const { return goalCol_; }

    /**
     * @brief Prints the maze to the specified output stream (for terminal debugging).
     * @param os The output stream object, defaults to std::cout.
     * @note Used for debugging and logging, will NOT be displayed on GUI.
     */
    void print(std::ostream &os = std::cout) const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<CellType> > grid_;

    // 初始化默认值为 -1，表示尚未设置起终点
    int startRow_ = -1;
    int startCol_ = -1;
    int goalRow_ = -1;
    int goalCol_ = -1;
};
