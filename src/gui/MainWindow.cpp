#include "../../include/MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    constexpr int INTIAL_MAZE_SIZE = 10;
    maze = new Maze(INTIAL_MAZE_SIZE, INTIAL_MAZE_SIZE);

    initUI();
}

void MainWindow::initialize_maze_configuration() {

    mazeConfig = new MazeConfigurationGui();

    splitter->addWidget(mazeWidget);
    splitter->addWidget(mazeConfig);

    splitter->setSizes({600, 100});
    splitter->setCollapsible(1, false);

    setCentralWidget(splitter);
}

void MainWindow::init_maze_generation_button_action() {
    connect(mazeConfig, &MazeConfigurationGui::generate_maze, this,
            [this](int width, int height, const QString& algorithm, const int seed) {

                delete maze;
                maze = new Maze(width, height);
                maze->setSeed(seed);

                maze->generate(algorithm.toStdString());

                mazeWidget->drawMaze(*maze);
            });
}

void MainWindow::initUI() {
    setWindowTitle("Maze");
    //init layout
    central = new QWidget(this);
    layout = new QVBoxLayout(central);
    central->setLayout(layout);

    splitter = new QSplitter(Qt::Vertical, this);

    mazeWidget = new MazeWidget(*maze, this);

    initialize_maze_configuration();

    init_maze_generation_button_action();


}

