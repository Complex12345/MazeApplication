#include <stack>
#include <vector>

#include "../../include/Maze.h"
#include "../../include/MazeGenerator.h"


class DfsGeneratorCpu: public MazeGenerator {
    static void mark_cell_as_visited(Maze &maze, std::vector<bool> visited, Maze::cell cell) {
        visited[cell.y * maze.getWidth() + cell.x] = true;
    }


    void generate(Maze &maze) override {
        std::vector<bool> visited(maze.getWidth() * maze.getHeight(), false);

        std::mt19937 rng(maze.getSeed());

        std::uniform_int_distribution<int> rng_width(0, maze.getWidth() - 1);
        std::uniform_int_distribution<int> rng_height(0, maze.getHeight() - 1);

        Maze::cell random_cell{rng_width(rng), rng_height(rng)};

        // init stack
        std::stack<Maze::cell> stack;
        stack.push(random_cell);
        mark_cell_as_visited(maze, visited, random_cell);


        // while (!stack.empty()) {
        //     Maze::cell current_cell = stack.top();
        //
        //
        //
        //
        // }




    }
    std::string name() const override {
        return "Recursive Backtracker";
    }
};