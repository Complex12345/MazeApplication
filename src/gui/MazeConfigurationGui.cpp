#include "../../include/MazeConfigurationGui.h"

#include <iostream>
#include <string>
#include <array>
#include <cuda_runtime.h>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>

#include "SystemInfo.h"


MazeConfigurationGui::MazeConfigurationGui(QWidget *parent) : QWidget(parent) {
    initMaze();
}

void MazeConfigurationGui::initDevices(QComboBox* combo_box) {

    const std::string cpuName = getCpuName();
    combo_box->addItem(QString::fromStdString(cpuName));

    const std::vector<std::string> gpuNames = getGpuNames();
    for (const auto &gpuName : gpuNames) {
        combo_box->addItem(QString::fromStdString(gpuName));
    }
}


void debugWidget(QList<QWidget*> widgets) {
    QStringList colors = {"lightblue", "lightgreen", "lightcoral"};

    for (int i = 0; i < widgets.size(); ++i) {
        widgets[i]->setStyleSheet("background-color: " + colors[i] + ";");
    }
}

void initLeftWidget(QWidget *left) {
    auto layout = new QVBoxLayout(left);
    auto *devices = new QComboBox(left);
    MazeConfigurationGui::initDevices(devices);
    layout->addWidget(devices);

}

void initSeedMenu(QVBoxLayout *centerLayout) {
    const auto widget = new QWidget();
    auto *horizontalLayout = new QHBoxLayout(widget);

    const auto *validator = new QIntValidator(INT32_MIN, INT32_MAX, widget);
    const auto seedInput = new QLineEdit(widget);
    seedInput->setValidator(validator);

    horizontalLayout->addWidget(seedInput);

    centerLayout->addWidget(widget);



}

void initCenterWidget(QWidget *center) {
    std::cout << "init center" << std::endl;
    auto layout = new QVBoxLayout(center);
    initSeedMenu(layout);

}




void initRightWidget(QWidget *right) {


}

void MazeConfigurationGui::initMaze() {
    // init widgets
    left = new QWidget(this);
    center = new QWidget(this);
    right = new QWidget(this);

    //init functions
    initLeftWidget(left);
    initCenterWidget(center);
    initRightWidget(right);

    debugWidget({left, center, right});

    auto *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(left);
    horizontalLayout->addWidget(center);
    horizontalLayout->addWidget(right);

    horizontalLayout->setStretch(0, 1);
    horizontalLayout->setStretch(1, 2);
    horizontalLayout->setStretch(2, 1);





    // devices = new QComboBox(this);
    // initDevices(devices);


    // layout = new QVBoxLayout(this);
    // layout->addWidget(devices);




}










