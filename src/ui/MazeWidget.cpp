#include "ui/MazeWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>
#include <QTimer>
#include <iostream>

QColor colorFor(CellType type)
{
    switch (type)
    {

    case CellType::Wall:
        return QColor(0x22, 0x22, 0x22);
    case CellType::Passage:
        return QColor(0xff, 0xff, 0xff);
    case CellType::Start:
        return QColor(0x2e, 0xa0, 0x43);
    case CellType::Goal:
        return QColor(0xd9, 0x3f, 0x3f);
    default:
        return QColor(0xff, 0xff, 0xff);
    }
}

MazeWidget::MazeWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(200, 200);

    connect(&animationTimer_, &QTimer::timeout, this, [this]
        {
            if (!generationResult_ ||
                animationIndex_ >= static_cast<int>(generationResult_->steps.size()))
            {
                animationTimer_.stop();
                playMazeGeneration_ = false;
                animationIndex_ = 0;
                update();
                return;
            }

            // 每次定时器触发，播放下一步
            ++animationIndex_;

            update();
        });
}

void MazeWidget::setGenerationResult(const GenerationResult &result)
{
    generationResult_ = result; // 设定属性

    animationTimer_.stop();
    playMazeGeneration_ = true; // 开始播放动画
    animationIndex_ = 0;
    animationTimer_.start(50);
}

void MazeWidget::setCell(int row, int col, CellType type)
{
    if (generationResult_ && generationResult_->maze.inBound(row, col))
    {
        generationResult_->maze.set(row, col, type);
        update(cellRect(row, col));
    }
}

void MazeWidget::setPathfindingResult(const PathfindingResult& result)
{
    searchSteps_ = result.steps;
    path_ = result.path;

    update();
}

int MazeWidget::cellSize() const
{
    if (!generationResult_)
        return 0;
    const int w = width() / generationResult_->maze.cols();
    const int h = height() / generationResult_->maze.rows();
    return std::min(w, h);
}

QPoint MazeWidget::origin() const
{
    if (!generationResult_)
        return QPoint(0, 0);
    const int size = cellSize();
    const int x = (width() - size * generationResult_->maze.cols()) / 2;
    const int y = (height() - size * generationResult_->maze.rows()) / 2;
    return QPoint(x, y);
}

QRect MazeWidget::cellRect(int row, int col) const
{
    if (!generationResult_)
        return QRect();
    const int size = cellSize();
    const QPoint org = origin();
    return QRect(org.x() + col * size, org.y() + row * size, size, size);
}

QRect MazeWidget::mazeRect() const
{
    if (!generationResult_)
        return QRect();
    const int size = cellSize();
    const QPoint org = origin();
    return QRect(org.x(), org.y(), generationResult_->maze.cols() * size, generationResult_->maze.rows() * size);
}

void MazeWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.fillRect(rect(), QColor(0xf0, 0xf0, 0xf0));

    if (!generationResult_ || cellSize() == 0)
        return;

    const int rows = generationResult_->maze.rows();
    const int cols = generationResult_->maze.cols();

    // 绘制迷宫生成动画
    if (playMazeGeneration_)
    {
        painter.fillRect(mazeRect(), QColor(0x22, 0x22, 0x22));

        const int lastIndex = std::min(
            animationIndex_,
            static_cast<int>(generationResult_->steps.size())
        );

        for (int i = 0; i < lastIndex; i++)
        {
            const auto& step = generationResult_->steps[i];

            painter.fillRect(
                cellRect(step.row, step.col),
                colorFor(step.type)
            );
        }

        return;
    }

    // 绘制静态迷宫
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            painter.fillRect(
                cellRect(r, c),
                colorFor(generationResult_->maze.at(r, c))
            );
        }
    }

    // 绘制 A* 最终路径：蓝色
    for (const auto& [row, col] : path_)
    {
        painter.fillRect(
            cellRect(row, col),
            QColor(0x35, 0x85, 0xe5)
        );
    }

    // 最后重新绘制起点和终点，避免被路径颜色覆盖
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            const CellType type = generationResult_->maze.at(r, c);

            if (type == CellType::Start || type == CellType::Goal)
            {
                painter.fillRect(cellRect(r, c), colorFor(type));
            }
        }
    }
}

QSize MazeWidget::sizeHint() const
{
    return {600, 600}; // 布局系统参考的"理想尺寸"
}

void MazeWidget::mousePressEvent(QMouseEvent *event)
{
    const int s = cellSize();
    if (!generationResult_ || s == 0)
    {
        return;
    }
    const QPoint p = event->position().toPoint() - origin();
    const int col = p.x() / s;
    const int row = p.y() / s;
    if (generationResult_->maze.inBound(row, col))
    {
        emit cellClicked(row, col);
    }
}