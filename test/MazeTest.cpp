
#include "../include/Maze.h"


int main() {
    constexpr int width = 10;
    constexpr int height = 10;

    Maze maze(width, height);
    maze.setSeed(1);
    maze.to_string();




    return 0;
}
