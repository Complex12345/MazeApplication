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


class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QVBoxLayout *layout = nullptr;
    QLabel *editor= nullptr;
    QLabel *console= nullptr;
    QWidget *central = nullptr;
    QSplitter *splitter = nullptr;
    QWidget *maze = nullptr;
    QWidget *configuration = nullptr;

    void initUI();




public:
    explicit MainWindow(QWidget *parent = nullptr);
};


#endif //MYQTCUDAPROJECT_MAINWINDOW_H
