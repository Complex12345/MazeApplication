#pragma once

#ifndef MYQTCUDAPROJECT_MAINWINDOW_H
#define MYQTCUDAPROJECT_MAINWINDOW_H


#pragma once
#include <QMainWindow>
#include <QSplitter>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QApplication>
#include <QTextStream>

#include "MazeConfigurationGui.h"
#include "MazeWidget.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    Maze *maze = nullptr;

private:
    MazeWidget *mazeWidget = nullptr;
    QVBoxLayout *layout = nullptr;
    QLabel *editor= nullptr;
    QLabel *console= nullptr;
    QWidget *central = nullptr;
    QSplitter *splitter = nullptr;
    QWidget *configuration = nullptr;
    MazeConfigurationGui *mazeConfig = nullptr;


    void initUI();




public:
    explicit MainWindow(QWidget *parent = nullptr);

    void initialize_maze_configuration();

    void init_maze_generation_button_action();
};


#endif //MYQTCUDAPROJECT_MAINWINDOW_H
