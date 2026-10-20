# 人工智能与创新 (C++) 大作业
递归分割迷宫生成与A*寻路算法的可视化实现——基于Qt的交互式平台

## Project Structure
```text
CourseProject/
├── CMakeLists.txt 
├── README.md                   # Project documentation, rules, and TODO list
├── .gitignore 
│
├── src/                        # Source code
│   ├── core/                   # Pure algorithms and models (NO Qt dependency)
│   │   ├── Cell.h              # Cell type definitions (Wall, Passage, Start, Goal)
│   │   ├── MazeMap.h/.cpp      # Grid data structure, start/goal points, bounds checking
│   │   ├── RecursiveDivisionGenerator.h/.cpp  # Maze generation algorithm
│   │   └── AStarSolver.h/.cpp  # A* pathfinding algorithm, outputs search steps
│   │
│   ├── ui/                     # Qt GUI 
│   │   ├── MainWindow.h/.cpp   # Main window, layout, signal/slot connections
│   │   ├── MazeWidget.h/.cpp   # Custom QWidget to draw the maze and animations
│   │   └── ControlPanel.h/.cpp # Buttons (Generate, Start, Pause, Step, Speed)
│   │
│   └── main.cpp                # Entry point (initializes QApplication and MainWindow)
│
├── tests/                      # Unit tests
│   ├── CMakeLists.txt          # Test build configuration (Catch2)
│   ├── test_maze.cpp           # Tests for MazeMap and RecursiveDivisionGenerator
│   └── test_astar.cpp          # Tests for A* solver (path validity, edge cases)
│
├── assets/                     # Raw materials
│   ├── icons/                  # Button icons, start/goal markers
│   └── styles/                 # QSS stylesheets (optional)
│
├── resources/                  # Qt resource files
│   └── resources.qrc           # Maps files in assets/ to Qt resource system
│
└── docs/                       # Documentation
    └── test_cases.md           # Detailed test cases documentation
```