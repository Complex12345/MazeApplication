#ifndef MYQTCUDAPROJECT_MAZECONFIGURATIONGUI_H
#define MYQTCUDAPROJECT_MAZECONFIGURATIONGUI_H

#include <QSpinBox>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class MazeConfigurationGui : public QWidget {
    Q_OBJECT

public:
    explicit MazeConfigurationGui(QWidget *parent = nullptr);

    signals:
        void generate_maze(int width, int height, QString algorithm, int seed);
        void solve_maze(QString algorithm);
        void set_speed(int delay_ms);
        void toggle_gpu(bool use_gpu);

public:
    static void init_devices(QComboBox *combo_box);

private:
    // Core layout sections
    QWidget *left_panel = nullptr;
    QWidget *center_panel = nullptr;
    QWidget *right_panel = nullptr;

    // UI elements
    QSpinBox *width_spin = nullptr;
    QSpinBox *height_spin = nullptr;
    QSpinBox *seed_spin = nullptr;
    QComboBox *gen_algorithm_box = nullptr;
    QComboBox *search_algorithm_box = nullptr;
    QComboBox *devices_box = nullptr;
    QSlider *speed_slider = nullptr;
    QCheckBox *gpu_check = nullptr;

    QPushButton *generate_button = nullptr;
    QPushButton *solve_button = nullptr;
    QPushButton *pause_button = nullptr;
    QPushButton *reset_button = nullptr;

    // Initialization functions
    void init_maze();
    void init_left_panel();
    void init_center_panel();
    void init_right_panel();
    void init_seed_menu(QVBoxLayout *center_layout);
    void init_maze_config_menu(QVBoxLayout *center_layout);
};

#endif // MYQTCUDAPROJECT_MAZECONFIGURATIONGUI_H
