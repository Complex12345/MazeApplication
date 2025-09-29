#pragma once

#ifndef MYQTCUDAPROJECT_MAINWINDOW_H
#define MYQTCUDAPROJECT_MAINWINDOW_H
#include <QMainWindow>

#include "MainWindow.h"


class MainWindow : public QMainWindow {
private:
    Q_OBJECT


public:
    explicit MainWindow(QWidget* parent = nullptr);
};


#endif //MYQTCUDAPROJECT_MAINWINDOW_H
