#include "../include/MazeWidget.h"

#include <QPainter>
#include <QPainterPath>
MazeWidget::MazeWidget(const Maze &maze, QWidget *parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    setRenderHint(QPainter::Antialiasing, false);
    setAlignment(Qt::AlignCenter);
    setCacheMode(CacheBackground);
    drawMaze(maze);
}


void MazeWidget::drawMaze(const Maze &maze) {
    QGraphicsScene *scene = this->scene();
    scene->clear();

    QPainterPath path;
    const int cell_size = 10; // smaller cells render faster

    for (int y = 0; y < maze.getHeight(); ++y) {
        for (int x = 0; x < maze.getWidth(); ++x) {
            uint8_t cell = maze.get_cell(x, y);
            int x0 = x * cell_size;
            int y0 = y * cell_size;
            int x1 = x0 + cell_size;
            int y1 = y0 + cell_size;

            if (cell & Maze::NORTH) path.moveTo(x0, y0), path.lineTo(x1, y0);
            if (cell & Maze::WEST)  path.moveTo(x0, y0), path.lineTo(x0, y1);
            if (cell & Maze::EAST)  path.moveTo(x1, y0), path.lineTo(x1, y1);
            if (cell & Maze::SOUTH) path.moveTo(x0, y1), path.lineTo(x1, y1);
        }
    }

    QPen pen(Qt::white);
    pen.setWidth(1);
    scene->addPath(path, pen);

    scene->setSceneRect(0, 0, maze.getWidth() * cell_size, maze.getHeight() * cell_size);
}


void MazeWidget::wheelEvent(QWheelEvent *event) {
    QGraphicsView::wheelEvent(event);
}

void MazeWidget::mousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);
}

void MazeWidget::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
}
