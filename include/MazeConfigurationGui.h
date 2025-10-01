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
        void generateMaze(int with, int heigh, QString algorithm, int seed);

    void solveMaze(QString algorithm);
    void setSpeed(int delayMs);
    void toggleGpu(bool useGpu);


private:
    QVBoxLayout *layout;
    QSpinBox *widthSpin;
    QSpinBox *heightSpin;
    QSpinBox *seedSpin;
    QComboBox *genAlgorithmBox;
    QComboBox *searchAlgorithmBox;
    QComboBox *devices;
    QSlider *speedSlider;
    QCheckBox *gpuCheck;

    QPushButton *generateButton;
    QPushButton *solveButton;
    QPushButton *pauseButton;
    QPushButton *resetButton;


    void initMaze();
    static void initDevices(QComboBox *combo_box);

};


#endif //MYQTCUDAPROJECT_MAZECONFIGURATIONGUI_H

