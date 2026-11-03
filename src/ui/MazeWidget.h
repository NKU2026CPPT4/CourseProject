#pragma once
#include <QWidget>
#include <optional>
#include "core/MazeMap.h"

class MazeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MazeWidget(QWidget *parent = nullptr);

    void setMaze(const MazeMap &maze);             // 整张图替换
    void setCell(int row, int col, CellType type); // 改一格

signals:
    void cellClicked(int row, int col);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    [[nodiscard]] QSize sizeHint() const override;

private:
    [[nodiscard]] int cellSize() const;
    [[nodiscard]] QPoint origin() const;
    [[nodiscard]] QRect cellRect(int row, int col) const;

    std::optional<MazeMap> maze_;
};