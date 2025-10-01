//
// Created by rayya on 2025-10-01.
//

#ifndef MYQTCUDAPROJECT_MAZE_H
#define MYQTCUDAPROJECT_MAZE_H
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Maze {
public:
    Maze(int width, int height);

    void generate(int seed, const string& algorithm);
    void solve(const string& algorithm);

    const vector<vector<int>>& getGrid() const { return grid; }

private:
    int width;
    int height;
    vector<vector<int>> grid;
};


#endif //MYQTCUDAPROJECT_MAZE_H