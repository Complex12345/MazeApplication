#include "../../include/generators/CpuPrimGenerator.h"
#include <random>

void CpuPrimGenerator::add_cell_if_valid(
    const std::vector<std::vector<Maze::CellType> > &grid,
    std::vector<Passage> &cells,
    const Maze::Cell &cell,
    const std::vector<std::vector<bool> > &visited) const {

    for (auto &dir: dirs) {
        const int x = cell.x + dir[0];
        const int y = cell.y + dir[1];
        if (check_is_valid(x, y) && grid[y][x] == Maze::CellType::wall && !visited[y][x]) {
            cells.push_back({cell, {x, y}});
        }
    }
}

void CpuPrimGenerator::generate(Maze &maze) {
    width = maze.getWidth();
    height = maze.getHeight();

    std::vector<std::vector<Maze::CellType> > &grid = maze.grid;
    const unsigned int seed = maze.getSeed();

    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> rng_width(1, width - 2);
    std::uniform_int_distribution<int> rng_height(2, height - 2);

    maze.fill_wall();

    std::vector<Passage> cells;
    std::vector<std::vector<bool> > visited(height, std::vector<bool>(width, false));

    const int starting_x = rng_width(rng);
    const int starting_y = rng_height(rng);
    Maze::Cell start_cell{starting_x, starting_y};

    visited[starting_y][starting_x] = true;
    grid[starting_y][starting_x] = Maze::CellType::path;

    add_cell_if_valid(grid, cells, start_cell, visited);

    while (!cells.empty()) {
        std::uniform_int_distribution<int> dist(0, (int) cells.size() - 1);
        int random_index = dist(rng);
        Passage passage = cells[random_index];
        cells.erase(cells.begin() + random_index);

        int next_x = passage.nextCell.x;
        int next_y = passage.nextCell.y;

        if (visited[next_y][next_x])
            continue;

        int mid_x = (passage.startingCell.x + next_x) / 2;
        int mid_y = (passage.startingCell.y + next_y) / 2;
        grid[mid_y][mid_x] = Maze::CellType::path;
        grid[next_y][next_x] = Maze::CellType::path;

        visited[next_y][next_x] = true;
        add_cell_if_valid(grid, cells, passage.nextCell, visited);
    }
}

bool CpuPrimGenerator::check_is_valid(int row, int col) const {
    return (1 <= row && row < height - 1 && 1 <= col && col < width - 1);
}
