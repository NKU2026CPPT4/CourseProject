#include "ui/MainWindow.h"

#include <QLabel>
#include <QStatusBar>

#include "core/DFSGenerator.h"
#include "core/AStarSolver.h"
#include "ui/MazeWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Maze Generation and Solution"));
    resize(900, 600);

    // 创建迷宫绘制组件
    auto mazeWidget = new MazeWidget(this);
    setCentralWidget(mazeWidget);

    // 第一步：生成迷宫
    DFSGenerator generator(4342);

    GenerationResult generationResult =
        generator.generateWithSteps(21, 21);

    // 将迷宫交给界面显示
    mazeWidget->setGenerationResult(generationResult);

    // 第二步：创建 A* 寻路算法对象
    AStarSolver solver;

    // 第三步：运行 A* 算法
    PathfindingResult pathResult =
        solver.solve(generationResult.maze);

    // 第四步：将寻路结果交给界面
    mazeWidget->setPathfindingResult(pathResult);

    // 显示寻路结果
    if (pathResult.success)
    {
        const int pathLength =
            static_cast<int>(pathResult.path.size()) - 1;

        statusBar()->showMessage(
            tr("A* found a path! Path length: %1").arg(pathLength)
        );
    }
    else
    {
        statusBar()->showMessage(tr("A* could not find a path."));
    }

    // 鼠标点击事件
    connect(mazeWidget, &MazeWidget::cellClicked,
        this, [this](int row, int col)
        {
            statusBar()->showMessage(
                tr("Cell clicked: (%1, %2)").arg(row).arg(col)
            );
        });
}