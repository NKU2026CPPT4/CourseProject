#pragma once
#include <QWidget>
#include <optional>
#include "core/MazeMap.h"
#include "core/Step.h"
#include <vector>
#include <utility>
#include <QTimer>

/**
 * @brief Maze widget.
 */
class MazeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MazeWidget(QWidget *parent = nullptr);

    void setGenerationResult(const GenerationResult &maze); // 整张图替换
    void setCell(int row, int col, CellType type);          // 改一格
    // 设置 A* 寻路结果
    void setPathfindingResult(const PathfindingResult &result);
    void setPathfindingResult();
    // 迷宫生成动画
    void playMazeGeneration(int intervalMs);
    bool playMazeGeneration_ = false;

    // 寻路动画
    void playPathFinding(int intervalMs);
    bool playPathFinding_ = false;
signals:
    void cellClicked(int row, int col);

protected:
    void paintEvent(QPaintEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    [[nodiscard]] QSize sizeHint() const override;

private:
    [[nodiscard]] int cellSize() const;
    [[nodiscard]] QPoint origin() const;
    [[nodiscard]] QRect cellRect(int row, int col) const;
    [[nodiscard]] QRect mazeRect() const;
    std::optional<GenerationResult> generationResult_;

    int animationIndex_ = 0;
    QTimer animationTimer_; // 迷宫生成动画

    int pathFindingIndex_ = 0;
    QTimer pathFindingTimer_; // 寻路动画

    // A* 搜索结果
    std::vector<SearchStep> searchSteps_;
    std::vector<std::pair<int, int>> path_;
};