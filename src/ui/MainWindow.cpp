#include "ui/MainWindow.h"
#include <QLabel>
#include <QStatusBar>
#include "core/DFSGenerator.h"
#include "ui/MazeWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("Maze Generation and Solution"));
    resize(900, 600);

    //auto *placeholder = new QLabel(tr("Maze Canvas"), this);
    //placeholder->setAlignment(Qt::AlignCenter);
    //setCentralWidget(placeholder);
    auto mazeWidget = new MazeWidget(this);
    setCentralWidget(mazeWidget);

    DFSGenerator generator(442);
    mazeWidget->setMaze(generator.generate(21, 21));

    connect(mazeWidget, &MazeWidget::cellClicked, this, [this](int row, int col) {
        statusBar()->showMessage(tr("Cell clicked: (%1, %2)").arg(row).arg(col));
    });

    statusBar()->showMessage(tr("Ready."));
}
