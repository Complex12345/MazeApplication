#include <QApplication>

#include "../include/MainWindow.h"

constexpr int SCREEN_WIDTH_SIZE = 1000;
constexpr int SCREEN_HEIGHT_SIZE = 600;

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    application.setWindowIcon(QIcon("../maze.png"));

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Maze Application");
    mainWindow.resize(SCREEN_WIDTH_SIZE, SCREEN_HEIGHT_SIZE);
    mainWindow.show();
    return QApplication::exec();
}
