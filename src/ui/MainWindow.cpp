#include "ui/MainWindow.h"

#include <QLabel>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("Maze Generation and Solution"));
    resize(900, 600);

    auto *placeholder = new QLabel(tr("Maze Canvas"), this);
    placeholder->setAlignment(Qt::AlignCenter);
    setCentralWidget(placeholder);

    statusBar()->showMessage(tr("Ready."));
}
