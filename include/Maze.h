#ifndef MYQTCUDAPROJECT_MAZE_H
#define MYQTCUDAPROJECT_MAZE_H

#include <cstdint>
#include <string>
#include <vector>

class Maze {
public:
    virtual ~Maze() = default;
    Maze(int width, int height);

    void draw_maze_top_walls(int y) const;

    void draw_maze_east_and_west_walls(int y) const;

    void draw_maze_south_walls(int y) const;

    void generate(const std::string& algorithm);

    enum Direction : uint8_t {
        NORTH = 1 << 0,
        EAST  = 1 << 1,
        SOUTH = 1 << 2,
        WEST  = 1 << 3
    };

    struct cell {
        int x;
        int y;
    };

    static bool has_wall(uint8_t cell, Direction dir) noexcept {
        return cell & dir;
    }

    static void set_wall(uint8_t &cell, Direction dir, bool present) noexcept {
        if (present)
            cell |= dir;
        else
            cell &= ~dir;
    }

    uint8_t get_cell(int x, int y) const noexcept {
        return grid[y * width + x];
    }

    void set_cell(int x, int y, uint8_t cell) noexcept {
        grid[y * width + x] = cell;
    }

    static void toggle_wall(uint8_t &cell, Direction dir) noexcept {
        cell ^= dir;
    }

    bool is_valid(int x, int y) const noexcept {
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    void solve(int seed, const std::string &algorithm);
    void setSeed(unsigned int new_seed) noexcept { seed = new_seed; }

    void to_string() const;

    [[nodiscard]] int getHeight() const noexcept { return height; }
    [[nodiscard]] int getWidth() const noexcept { return width; }
    [[nodiscard]] unsigned int getSeed() const noexcept { return seed; }

    std::vector<uint8_t> grid;

private:
    const int width;
    const int height;
    unsigned int seed;
    static constexpr uint8_t WALL = NORTH | EAST | SOUTH | WEST;
};

#endif // MYQTCUDAPROJECT_MAZE_H
