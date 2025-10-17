#ifndef MYQTCUDAPROJECT_MAZEGENERATOR_H
#define MYQTCUDAPROJECT_MAZEGENERATOR_H
#include <random>
#include <string>

class Maze;

class MazeGenerator {
public:
    virtual void generate(Maze& maze) = 0;
    [[nodiscard]] virtual std::string name() const = 0;
    virtual ~MazeGenerator() = default;

    std::vector<std::vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};



};

#endif //MYQTCUDAPROJECT_MAZEGENERATOR_H