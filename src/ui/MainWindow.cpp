#include "ui/MainWindow.h"

#include <QLabel>
#include <QStatusBar>
#include <QToolBar>
#include <QPushButton>

#include "core/DFSGenerator.h"
#include "core/AStarSolver.h"
#include "ui/MazeWidget.h"

void MainWindow::generateMaze()
{
    mazeWidget->setPathfindingResult();
    std::random_device rd;
    DFSGenerator generator(rd());

    generationResult =
        generator.generateWithSteps(21, 21);

    // 将迷宫交给界面显示
    mazeWidget->setGenerationResult(*generationResult);
    mazeWidget->playMazeGeneration(50);
}

void MainWindow::findPath()
{ 
    AStarSolver solver;

    // 运行 A* 算法
    PathfindingResult pathResult =
        solver.solve(generationResult->maze);

    // 将寻路结果交给界面
    mazeWidget->setPathfindingResult(pathResult);
    mazeWidget->playPathFinding(60);

    // 显示寻路结果
    if (pathResult.success)
    {
        const int pathLength =
            static_cast<int>(pathResult.path.size()) - 1;

        statusBar()->showMessage(
            tr("A* 找到了一条路径! 路径长度: %1").arg(pathLength));
    }
    else
    {
        statusBar()->showMessage(tr("A* 无法找到一条路径."));
    }
    
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("迷宫生成与寻路可视化"));
    resize(900, 600);

    // 创建迷宫绘制组件
    mazeWidget = new MazeWidget(this);
    setCentralWidget(mazeWidget);

    // 创建toolbar
    auto *toolbar = new QToolBar(tr("工具栏"), this);
    addToolBar(toolbar);

    auto *generateButton = new QPushButton(tr("生成迷宫"), toolbar);
    toolbar->addWidget(generateButton);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateMaze);

    auto *findPathButton = new QPushButton(tr("寻找路径"), toolbar);
    toolbar->addWidget(findPathButton);
    connect(findPathButton, &QPushButton::clicked, this, &MainWindow::findPath);

    // 鼠标点击事件
    connect(mazeWidget, &MazeWidget::cellClicked,
            this, [this](int row, int col)
            { statusBar()->showMessage(
                  tr("格子被点击: (%1, %2)").arg(row).arg(col)); });
}