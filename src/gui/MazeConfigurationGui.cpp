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

/*!
    \class MazeConfigurationGui
    \brief The MazeConfigurationGui class shows the configuration GUI to use application
*/

MazeConfigurationGui::MazeConfigurationGui(QWidget *parent)
    : QWidget(parent) {
    init_maze();
}

// Device Initialization
void MazeConfigurationGui::init_devices(QComboBox *combo_box) {
    const std::string cpu_name = getCpuName();
    combo_box->addItem(QString::fromStdString(cpu_name));

    const std::vector<std::string> gpu_names = getGpuNames();
    for (const auto &gpu_name : gpu_names) {
        combo_box->addItem(QString::fromStdString(gpu_name));
    }
}

// Debug
inline void debug_widget(const QList<QWidget *> &widgets) {
    QStringList colors = {"lightblue", "lightgreen", "lightcoral"};
    for (int i = 0; i < widgets.size(); ++i) {
        widgets[i]->setStyleSheet("background-color: " + colors[i] + ";");
    }
}

// Left Panel
void MazeConfigurationGui::init_left_panel() {
    auto *left_layout = new QVBoxLayout(left_panel);
    devices_box = new QComboBox(left_panel);
    init_devices(devices_box);
    left_layout->addWidget(devices_box);
}

// Center Panel
void MazeConfigurationGui::init_seed_menu(QVBoxLayout *center_layout) {
    // container widget
    auto *container_widget = new QWidget(center_layout->parentWidget());
    auto *horizontal_layout = new QHBoxLayout(container_widget);

    //seed label
    auto *seed_label = new QLabel("Seed:", container_widget);

    // seed input + validator
    auto *validator = new QIntValidator(0, INT32_MAX, container_widget);
    seed_input = new QLineEdit(container_widget);
    seed_input->setValidator(validator);

    // generate random seed button
    generate_button = new QPushButton("Generate", container_widget);
    random_button = new QPushButton("Random", container_widget);



    connect(random_button, &QPushButton::clicked, this, [validator, this]() {
        const int min = validator->bottom();
        const int max = validator->top();
        const int seed = QRandomGenerator::global()->bounded(min, max);
        seed_input->setText(QString::number(seed));
    });


    horizontal_layout->addWidget(seed_label);
    horizontal_layout->addWidget(seed_input);
    horizontal_layout->addWidget(generate_button);
    horizontal_layout->addWidget(random_button);
    center_layout->addWidget(container_widget);
}

void MazeConfigurationGui::init_generation_type_menu(QVBoxLayout *center_layout) {

    gen_algorithm_box = new QComboBox(center_layout->parentWidget());

    for (const auto &pair : gen_algo_map) {
        gen_algorithm_box->addItem(pair.second, static_cast<int>(pair.first));
    }

    center_layout->addWidget(gen_algorithm_box);
}


void MazeConfigurationGui::init_maze_config_menu(QVBoxLayout *center_layout) {
    auto *container_widget = new QWidget(center_layout->parentWidget());
    auto *horizontal_layout = new QHBoxLayout(container_widget);

    auto *algorithm_label = new QLabel("Algorithm:", container_widget);
}

void MazeConfigurationGui::init_center_panel() {
    std::cout << "init center" << std::endl;
    auto *center_layout = new QVBoxLayout(center_panel);
    center_layout->setAlignment(Qt::AlignTop);

    init_seed_menu(center_layout);
    init_generation_type_menu(center_layout);
}

// Right Panel
void MazeConfigurationGui::init_right_panel() {
    Q_UNUSED(right_panel);
    // placeholder
}

// Main Initialization
void MazeConfigurationGui::init_maze() {
    // Create sections
    left_panel = new QWidget(this);
    center_panel = new QWidget(this);
    right_panel = new QWidget(this);

    // Initialize each section
    init_left_panel();
    init_center_panel();
    init_right_panel();

    debug_widget({left_panel, center_panel, right_panel});

    connect(generate_button, &QPushButton::clicked, this, [this]() {
        int width = width_spin ? width_spin->value() : 10;
        int height = height_spin ? height_spin->value() : 10;
        QString algorithm = gen_algorithm_box ? gen_algorithm_box->currentText() : "DFS";
        int seed = seed_input ? seed_input->text().toInt() : 0;

        emit generate_maze(width, height, algorithm, seed);

    });

    // Set up layout
    auto *horizontal_layout = new QHBoxLayout(this);
    horizontal_layout->addWidget(left_panel);
    horizontal_layout->addWidget(center_panel);
    horizontal_layout->addWidget(right_panel);

    horizontal_layout->setStretch(0, 1);
    horizontal_layout->setStretch(1, 2);
    horizontal_layout->setStretch(2, 1);
}
