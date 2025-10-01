#include "../../include/MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    initUI();
}

void MainWindow::initUI() {
    setWindowTitle("Maze");
    //init layout
    central = new QWidget(this);
    layout = new QVBoxLayout(central);
    central->setLayout(layout);

    editor = new QLabel("Main workspace");
    console = new QLabel("Console / Output");

    //Split config and interface
    splitter = new QSplitter(Qt::Vertical, this);

    //init MazeConfig
    mazeConfig = new MazeConfigurationGui();

    splitter->addWidget(editor);
    splitter->addWidget(mazeConfig);

    splitter->setSizes({600, 100});
    splitter->setCollapsible(1, false);

    setCentralWidget(splitter);
}

