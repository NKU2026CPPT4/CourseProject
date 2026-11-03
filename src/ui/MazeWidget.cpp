#include "ui/MazeWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>

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
}

void MazeWidget::setMaze(const MazeMap &maze)
{
    maze_ = maze;
    update();
}

void MazeWidget::setCell(int row, int col, CellType type)
{
    if (maze_ && maze_->inBound(row, col))
    {
        maze_->set(row, col, type);
        update(cellRect(row, col));
    }
}

int MazeWidget::cellSize() const
{
    if (!maze_)
        return 0;
    const int w = width() / maze_->cols();
    const int h = height() / maze_->rows();
    return std::min(w, h);
}

QPoint MazeWidget::origin() const
{
    if (!maze_)
        return QPoint(0, 0);
    const int size = cellSize();
    const int x = (width() - size * maze_->cols()) / 2;
    const int y = (height() - size * maze_->rows()) / 2;
    return QPoint(x, y);
}

QRect MazeWidget::cellRect(int row, int col) const
{
    if (!maze_)
        return QRect();
    const int size = cellSize();
    const QPoint org = origin();
    return QRect(org.x() + col * size, org.y() + row * size, size, size);
}

void MazeWidget::paintEvent(QPaintEvent *event)
{
    const int s = cellSize();
    const QPoint o = origin();
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0xf0, 0xf0, 0xf0));
    if (!maze_ || cellSize() == 0)
        return;
    for (int r = 0; r < maze_->rows(); r++)
    {
        for (int c = 0; c < maze_->cols(); c++)
        {
            painter.fillRect(cellRect(r, c), colorFor(maze_->at(r, c)));
        }
    }
}

QSize MazeWidget::sizeHint() const {
    return {600, 600};   // 布局系统参考的"理想尺寸"
}

void MazeWidget::mousePressEvent(QMouseEvent *event)
{
    const int s=cellSize();
    if(!maze_ || s ==0){
        return;
    }
    const QPoint p=event->position().toPoint()-origin();
    const int col=p.x()/s;
    const int row=p.y()/s;
    if(maze_->inBound(row,col)){
        emit cellClicked(row,col);
    }
}