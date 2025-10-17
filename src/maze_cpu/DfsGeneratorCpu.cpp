#include <stack>
#include <vector>

#include "../../include/Maze.h"
#include "../../include/MazeGenerator.h"


class DfsGeneratorCpu: public MazeGenerator {
    static void mark_cell_as_visited(Maze &maze, std::vector<bool> visited, Maze::cell cell) {
        visited[cell.y * maze.getWidth() + cell.x] = true;
    }


    bool check_for_at_least_1_unvisited_neighbour(Maze &maze, std::vector<bool> visited, Maze::cell current_cell) const {
        for (std::vector<int> dir: dirs) {
            int x = current_cell.x + dir[0];
            int y = current_cell.y + dir[1];
            if (maze.is_valid(x, y) && !visited[y * maze.getWidth() + x]) {
                    return true;
            }
        }
        return false;
    }

    void generate(Maze &maze) override {
        std::vector<bool> visited(maze.getWidth() * maze.getHeight(), false);

        std::mt19937 rng(maze.getSeed());

        std::uniform_int_distribution<int> rng_width(0, maze.getWidth() - 1);
        std::uniform_int_distribution<int> rng_height(0, maze.getHeight() - 1);

        Maze::cell random_cell{rng_width(rng), rng_height(rng)};

        std::stack<Maze::cell> stack;
        stack.push(random_cell);
        mark_cell_as_visited(maze, visited, random_cell);


        while (!stack.empty()) {
            Maze::cell current_cell = stack.top();

            if (check_for_at_least_1_unvisited_neighbour(maze, visited, current_cell)) {
                int start = std::uniform_int_distribution<int>(0, 3)(rng);
                for (int i = 0; i < 4; ++i) {
                    int dir_index = (start + i) % 4;
                    Maze::Direction dir = walls_array[dir_index];

                    int nx = current_cell.x + remove_walls_map[dir][0];
                    int ny = current_cell.y + remove_walls_map[dir][1];

                    if (!maze.is_valid(nx, ny)) continue;
                    if (visited[ny * maze.getWidth() + nx]) continue;


                    Maze::cell next{nx, ny};

                    Maze::set_wall(maze.grid[current_cell.y * maze.getWidth() + current_cell.x], dir, false);
                    Maze::set_wall(maze.grid[ny * maze.getWidth() + nx], opposite_wall[dir], false);

                    stack.push(next);
                    visited[ny * maze.getWidth() + nx] = true;
                    break;
                }

            }
            else {
                stack.pop();
            }
        }




    }
    std::string name() const override {
        return "depth-first search";
    }
};