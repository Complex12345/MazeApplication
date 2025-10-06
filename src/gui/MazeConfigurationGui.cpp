#include "../../include/MazeConfigurationGui.h"

#include <iostream>
#include <string>
#include <array>
#include <cuda_runtime.h>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QIntValidator>
#include <QRandomGenerator>

#include "SystemInfo.h"

MazeConfigurationGui::MazeConfigurationGui(QWidget *parent)
    : QWidget(parent) {
    initMaze();
}


// Device Initialization
void MazeConfigurationGui::initDevices(QComboBox *combo_box) {
    const std::string cpuName = getCpuName();
    combo_box->addItem(QString::fromStdString(cpuName));

    const std::vector<std::string> gpuNames = getGpuNames();
    for (const auto &gpuName : gpuNames) {
        combo_box->addItem(QString::fromStdString(gpuName));
    }
}


// Debug
static void debugWidget(const QList<QWidget *> &widgets) {
    QStringList colors = {"lightblue", "lightgreen", "lightcoral"};
    for (int i = 0; i < widgets.size(); ++i) {
        widgets[i]->setStyleSheet("background-color: " + colors[i] + ";");
    }
}

// Left Panel
void MazeConfigurationGui::initLeftWidget(QWidget *left_widget) {
    auto *left_layout = new QVBoxLayout(left_widget);
    devices = new QComboBox(left_widget);
    initDevices(devices);
    left_layout->addWidget(devices);
}

// Center Panel
void MazeConfigurationGui::initSeedMenu(QVBoxLayout *centerLayout) {
    // create new widget to containerize widgets
    auto *widget = new QWidget(centerLayout->parentWidget());
    auto *horizontalLayout = new QHBoxLayout(widget);

    // seed input adn validator
    auto *validator = new QIntValidator(0, INT32_MAX, widget);
    auto *seedInput = new QLineEdit(widget);
    seedInput->setValidator(validator);

    // generate random seed button
    generateButton = new QPushButton("Generate", widget);

    connect(generateButton, &QPushButton::clicked, this, [seedInput, validator]() {
        const int min = validator->bottom();
        const int max = validator->top();

        const int seed = QRandomGenerator::global()->bounded(min, max);

        seedInput->setText(QString::number(seed));
    });


    horizontalLayout->addWidget(seedInput);
    horizontalLayout->addWidget(generateButton);

    centerLayout->addWidget(widget);
}

void MazeConfigurationGui::initCenterWidget(QWidget *centerWidget) {
    std::cout << "init center" << std::endl;
    auto *centerLayout = new QVBoxLayout(centerWidget);
    initSeedMenu(centerLayout);
}


// Right Panel
void MazeConfigurationGui::initRightWidget(QWidget *right_widget) {
    Q_UNUSED(right_widget);
    // placeholder
}

// Main Initialization
void MazeConfigurationGui::initMaze() {
    // Create sections
    left = new QWidget(this);
    center = new QWidget(this);
    right = new QWidget(this);

    // Initialize each section
    initLeftWidget(left);
    initCenterWidget(center);
    initRightWidget(right);

    debugWidget({left, center, right});

    // Set up layout
    auto *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(left);
    horizontalLayout->addWidget(center);
    horizontalLayout->addWidget(right);

    horizontalLayout->setStretch(0, 1);
    horizontalLayout->setStretch(1, 2);
    horizontalLayout->setStretch(2, 1);
}
