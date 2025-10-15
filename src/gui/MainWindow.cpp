#include "../../include/MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    maze = new Maze(1000, 1000);
    initUI();
}

void MainWindow::initUI() {
    setWindowTitle("Maze");
    //init layout
    central = new QWidget(this);
    layout = new QVBoxLayout(central);
    central->setLayout(layout);

    editor = new QLabel("Main workspace");
    mazeWidget = new MazeWidget(*maze, this);

    //Split config and interface
    splitter = new QSplitter(Qt::Vertical, this);

    //init MazeConfig
    mazeConfig = new MazeConfigurationGui();

    splitter->addWidget(mazeWidget);
    splitter->addWidget(mazeConfig);

    splitter->setSizes({600, 100});
    splitter->setCollapsible(1, false);

    setCentralWidget(splitter);
}

