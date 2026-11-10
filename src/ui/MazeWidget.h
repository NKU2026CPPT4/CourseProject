#pragma once
#include <QWidget>
#include <optional>
#include "core/MazeMap.h"
#include "core/Step.h"
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
signals:
    void cellClicked(int row, int col);

protected:
    void paintEvent(QPaintEvent *event) override;
    //void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    [[nodiscard]] QSize sizeHint() const override;

private:
    [[nodiscard]] int cellSize() const;
    [[nodiscard]] QPoint origin() const;
    [[nodiscard]] QRect cellRect(int row, int col) const;
    [[nodiscard]] QRect mazeRect() const;
    //void playAnimation();
    std::optional<GenerationResult> generationResult_;
    bool playMazeGeneration_ = false;
    int animationIndex_ = 0;
    QTimer animationTimer_;
};