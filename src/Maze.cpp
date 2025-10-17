#include "../include/Maze.h"
#include <iostream>

#include "../include/MazeGenerator.h"
#include "../src/maze_cpu/DfsGeneratorCpu.cpp"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmove-const-arg"

Maze::Maze(int width, int height)
    : width(width),
      height(height),
      seed(0),
      grid(width * height, WALL) {}

void Maze::draw_maze_top_walls(const int y) const {
    for (int x = 0; x < width; ++x) {
        const uint8_t cell = grid[y * width + x];
        std::cout << "+";
        if (cell & NORTH)
            std::cout << "---";
        else
            std::cout << "   ";
    }
    std::cout << "+\n";
}

void Maze::draw_maze_east_and_west_walls(const int y) const {
    for (int x = 0; x < width; ++x) {
        const uint8_t cell = grid[y * width + x];
        if (cell & WEST)
            std::cout << "|";
        else
            std::cout << " ";

        std::cout << "   ";


        if (x == width - 1) {
            if (cell & EAST)
                std::cout << "|";
            else
                std::cout << " ";
        }
    }
    std::cout << "\n";
}

void Maze::draw_maze_south_walls(const int y) const {
    if (y == height - 1) {
        for (int x = 0; x < width; ++x) {
            const uint8_t cell = grid[y * width + x];
            std::cout << "+";
            if (cell & SOUTH)
                std::cout << "---";
            else
                std::cout << "   ";
        }
        std::cout << "+\n";
    }
}

void Maze::to_string() const {
    for (int row = 0; row < height; ++row) {
        draw_maze_top_walls(row);
        draw_maze_east_and_west_walls(row);
        draw_maze_south_walls(row);
    }
}

void Maze::generate(const std::string &algorithm) {
    std::cout << "Generating maze with " << algorithm << " algorithm and seed: " << seed << "\n";
    std::unique_ptr<MazeGenerator> generator;

    if (algorithm == "Depth-First Search") {
        generator = std::make_unique<DfsGeneratorCpu>();
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << "\n";
        return;
    }

    generator->generate(*this);
}



#pragma clang diagnostic pop
