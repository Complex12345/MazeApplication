#ifndef MYQTCUDAPROJECT_CPUPRIMGENERATOR_H
#define MYQTCUDAPROJECT_CPUPRIMGENERATOR_H

#include "../MazeGenerator.h"
#include "../Maze.h"
#include <vector>
#include <random>

class CpuPrimGenerator final : public MazeGenerator {
public:
    void generate(Maze &maze) override;

    [[nodiscard]] std::string name() const override { return "Prim (CPU)"; }

private:
    int height, width;

    struct Passage {
        Maze::Cell startingCell;
        Maze::Cell nextCell;
    };

    std::vector<std::vector<int> > dirs = {{0, 2}, {2, 0}, {-2, 0}, {0, -2}};

    void add_cell_if_valid(const std::vector<std::vector<Maze::CellType> > &grid,
                           std::vector<Passage> &cells,
                           const Maze::Cell &cell,
                           const std::vector<std::vector<bool> > &visited) const;

    bool check_is_valid(int row, int col) const;
};

#endif // MYQTCUDAPROJECT_CPUPRIMGENERATOR_H
