#ifndef MYQTCUDAPROJECT_MAZEWIDGET_H
#define MYQTCUDAPROJECT_MAZEWIDGET_H

#include <QGraphicsView>

#include "Maze.h"

class MazeWidget : public QGraphicsView {
    Q_OBJECT

public:
    explicit MazeWidget(const Maze& maze, QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void drawMaze(const Maze& maze);
    QPoint last_mouse_pos;
    double scale_factor = 1.15;
};

#endif //MYQTCUDAPROJECT_MAZEWIDGET_H