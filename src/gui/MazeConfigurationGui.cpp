//
// Created by rayya on 2025-10-01.
//

#include "../../include/MazeConfigurationGui.h"

#include <iostream>
#include <string>
#include <array>
#include <intrin.h>
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


void MazeConfigurationGui::initMaze() {
    devices = new QComboBox(this);
    initDevices(devices);

    layout = new QVBoxLayout(this);
    layout->addWidget(devices);




}









