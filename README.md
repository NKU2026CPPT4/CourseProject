# 人工智能与创新 (C++) 大作业
基于深度优先搜索的随机迷宫生成与A*寻路算法的可视化实现——基于Qt的交互式平台

## Project Structure
```text
CourseProject/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── main.cpp                 # 程序入口，只负责启动 MainWindow
│   │
│   ├── core/                    # 【纯 C++】核心算法，绝对不包含 Qt 头文件
│   │   ├── MazeMap.h/.cpp       # 数据模型 (你写的)
│   │   ├── DFSGenerator.h/.cpp  # 迷宫生成 (你写的)
│   │   ├── AStarSolver.h/.cpp   # 寻路算法 (a 写的)
│   │   └── Step.h               # 动画动作结构体 (你定义的)
│   │
│   ├── ui/                      # 【Qt 界面】只负责显示和接收用户点击
│   │   ├── MainWindow.h/.cpp    # 主窗口，负责整体布局拼装（左画布，右面板）
│   │   ├── MazeWidget.h/.cpp    # 画布控件，只负责把 2D 数组画成黑方块
│   │   ├── ControlPanel.h/.cpp  # 右侧的控制面板（包含 Settings 和 Action 两个 GroupBox）
│   │   └── StatsPanel.h/.cpp    # 右下角的统计面板（未来显示耗时、访问节点数等）
│   │
│   └── app/                     # 【胶水层】连接 UI 和算法的大脑
│       └── AnimationController.h/.cpp # 负责用 QTimer 播放生成和寻路的动画
│
├── assets/                      # 原始素材（图标、字体）
├── resources/                   # Qt 资源文件（.qrc、QSS 样式表）
│   ├── resources.qrc
│   └── style.qss                # 把你刚才的 QSS 样式抽离到这里
└── tests/                       # 单元测试
```
