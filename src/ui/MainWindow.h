#pragma once

#include <QMainWindow>
#include <ui/MazeWidget.h>
#include "core/DFSGenerator.h"
#include "core/AStarSolver.h"

/**
 * @brief Main window widget.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    void generateMaze();
    void findPath();
    std::optional<GenerationResult> generationResult;
    MazeWidget *mazeWidget;

};
