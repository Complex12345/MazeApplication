#ifndef MYQTCUDAPROJECT_MAZEGENERATOR_H
#define MYQTCUDAPROJECT_MAZEGENERATOR_H
#include <array>
#include <random>
#include <string>
#include <unordered_map>

#include "Maze.h"

class Maze;

class MazeGenerator {
public:
    virtual void generate(Maze& maze) = 0;
    [[nodiscard]] virtual std::string name() const = 0;
    virtual ~MazeGenerator() = default;

    std::vector<std::vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};


    std::array<Maze::Direction, 4> walls_array = {
        Maze::NORTH, Maze::EAST, Maze::SOUTH, Maze::WEST
    };

    std::unordered_map<Maze::Direction, std::vector<int>> remove_walls_map = {
        { Maze::NORTH, { 0, -1 } },
        { Maze::EAST,  { 1,  0 } },
        { Maze::SOUTH, { 0,  1 } },
        { Maze::WEST,  { -1, 0 } }
    };

    std::unordered_map<Maze::Direction, Maze::Direction> opposite_wall = {
        { Maze::NORTH, Maze::SOUTH },
        { Maze::SOUTH, Maze::NORTH },
        { Maze::EAST,  Maze::WEST },
        { Maze::WEST,  Maze::EAST }
    };



};

#endif //MYQTCUDAPROJECT_MAZEGENERATOR_H