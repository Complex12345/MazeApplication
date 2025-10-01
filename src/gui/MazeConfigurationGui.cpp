#include "../../include/MazeConfigurationGui.h"

#include <iostream>
#include <string>
#include <array>
#include <cuda_runtime.h>

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

void initLeftWidget(QWidget *widget) {
    auto layout = new QVBoxLayout(widget);
    auto *devices = new QComboBox(widget);
    MazeConfigurationGui::initDevices(devices);
    layout->addWidget(devices);

}

void initCenterWidget(QWidget *center) {

}

void initRightWidget(QWidget *right) {

}

void MazeConfigurationGui::initMaze() {
    left = new QWidget(this);
    initLeftWidget(left);
    center = new QWidget(this);
    right = new QWidget(this);
    debugWidget({left, center, right});

    auto *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(left);
    horizontalLayout->addWidget(center);
    horizontalLayout->addWidget(right);

    horizontalLayout->setStretch(0, 1); // left takes 1 share
    horizontalLayout->setStretch(1, 2); // center takes 2 shares
    horizontalLayout->setStretch(2, 1); // right takes 1 share


    // devices = new QComboBox(this);
    // initDevices(devices);


    // layout = new QVBoxLayout(this);
    // layout->addWidget(devices);




}










