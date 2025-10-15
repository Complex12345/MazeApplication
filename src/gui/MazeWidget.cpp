#include "../include/MazeWidget.h"

#include <iostream>
#include <ostream>
#include <qcoreapplication.h>
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
    const int cell_size = 10;
    const int width_px  = maze.getWidth() * cell_size;
    const int height_px = maze.getHeight() * cell_size;

    QImage image(width_px + 1, height_px + 1, QImage::Format_RGB32);
    image.fill(Qt::black);

    QPainter painter(&image);
    painter.setPen(Qt::white);

    for (int y = 0; y < maze.getHeight(); ++y) {
        for (int x = 0; x < maze.getWidth(); ++x) {
            uint8_t cell = maze.get_cell(x, y);
            int x0 = x * cell_size;
            int y0 = y * cell_size;
            int x1 = x0 + cell_size;
            int y1 = y0 + cell_size;

            if (cell & Maze::NORTH) painter.drawLine(x0, y0, x1, y0);
            if (cell & Maze::WEST)  painter.drawLine(x0, y0, x0, y1);
            if (cell & Maze::EAST)  painter.drawLine(x1, y0, x1, y1);
            if (cell & Maze::SOUTH) painter.drawLine(x0, y1, x1, y1);
        }
    }

    painter.end();

    // Clear old scene and draw the single pixmap
    QGraphicsScene *scene = this->scene();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));

    scene->setSceneRect(0, 0, width_px + 1, height_px + 1);

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
