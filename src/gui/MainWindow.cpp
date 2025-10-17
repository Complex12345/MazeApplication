#include "../../include/MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    constexpr int INTIAL_MAZE_SIZE = 10;
    maze = new Maze(INTIAL_MAZE_SIZE, INTIAL_MAZE_SIZE);

    initUI();
}

void MainWindow::connect_signals() {
    connect(mazeConfig, &MazeConfigurationGui::generate_maze, this,
        [this](int width, int height, const QString &algorithm, int seed) {

        if (mazeWatcher && mazeWatcher->isRunning()) {
            qDebug() << "Maze generation already running, ignoring.";
            return;
        }

        if (mazeWidget && mazeWidget->scene())
            mazeWidget->scene()->clear();

        if (statusLabel) {
            statusLabel->setText("Generating...");
            statusLabel->setStyleSheet("color: orange;");
            statusLabel->repaint();
            QApplication::processEvents();
        }

        delete maze;

        maze = new Maze(width, height);
        maze->setSeed(seed);

        QFuture<void> future = QtConcurrent::run([this, algorithm]() {
            maze->generate(algorithm.toStdString());
        });

        if (!mazeWatcher)
            mazeWatcher = new QFutureWatcher<void>(this);

        static bool connected = false;
        if (!connected) {
            connect(mazeWatcher, &QFutureWatcher<void>::finished, this, [this]() {
                mazeWidget->drawMaze(*maze);
                statusLabel->setText("Done!");
                statusLabel->setStyleSheet("color: lightgreen;");
                QTimer::singleShot(3000, this, [this]() {
                    statusLabel->clear();
                });
                qDebug() << "Maze generation finished.";
            });
            connected = true;
        }

        mazeWatcher->setFuture(future);
    });
}


void MainWindow::initialize_maze_configuration() {
    mazeConfig = new MazeConfigurationGui();

    splitter->addWidget(mazeWidget);
    splitter->addWidget(mazeConfig);

    splitter->setSizes({600, 100});
    splitter->setCollapsible(1, false);

    setCentralWidget(splitter);
}


void MainWindow::initUI() {
    setWindowTitle("Maze");

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    setCentralWidget(central);

    splitter = new QSplitter(Qt::Vertical, this);
    mazeWidget = new MazeWidget(*maze, this);
    mazeConfig = new MazeConfigurationGui();

    splitter->addWidget(mazeWidget);
    splitter->addWidget(mazeConfig);

    statusLabel = new QLabel("Ready", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(statusLabel);
    layout->addWidget(splitter);

    mazeWatcher = new QFutureWatcher<void>(this);

    connect_signals();
}
