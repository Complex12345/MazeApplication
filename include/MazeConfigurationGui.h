#ifndef MYQTCUDAPROJECT_MAZECONFIGURATIONGUI_H
#define MYQTCUDAPROJECT_MAZECONFIGURATIONGUI_H

#include <QSpinBox>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>

class MazeConfigurationGui : public QWidget {
    Q_OBJECT

public:
    explicit MazeConfigurationGui(QWidget *parent = nullptr);

    signals:
        void generateMaze(int width, int height, QString algorithm, int seed);
    void solveMaze(QString algorithm);
    void setSpeed(int delayMs);
    void toggleGpu(bool useGpu);

public:
    static void initDevices(QComboBox *combo_box);

private:
    // Core layout sections
    QWidget *left = nullptr;
    QWidget *center = nullptr;
    QWidget *right = nullptr;

    // UI elements
    QVBoxLayout *layout = nullptr;
    QSpinBox *widthSpin = nullptr;
    QSpinBox *heightSpin = nullptr;
    QSpinBox *seedSpin = nullptr;
    QComboBox *genAlgorithmBox = nullptr;
    QComboBox *searchAlgorithmBox = nullptr;
    QComboBox *devices = nullptr;
    QSlider *speedSlider = nullptr;
    QCheckBox *gpuCheck = nullptr;

    QPushButton *generateButton = nullptr;
    QPushButton *solveButton = nullptr;
    QPushButton *pauseButton = nullptr;
    QPushButton *resetButton = nullptr;

    // Initialization functions
    void initMaze();
    void initLeftWidget(QWidget *left_widget);
    void initCenterWidget(QWidget *centerWidget);
    void initRightWidget(QWidget *right_widget);
    void initSeedMenu(QVBoxLayout *centerLayout);
};

#endif // MYQTCUDAPROJECT_MAZECONFIGURATIONGUI_H
