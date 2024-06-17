#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>


enum class State {
    kEmpty,
    kObstacle,
    kClosed,
    kPath,
    kStart,
    kFinish
};


const int delta[4][2] {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

std::vector<State> ParseBoardFile(std::string line)
{
    std::istringstream boardstream(line);
    int number;
    char character;
    std::vector<State> row;

    while (boardstream >> number >> character && character == ',')
    {
        if (number == 0)
        {
            row.push_back(State::kEmpty);
        }
        else
        {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}


std::vector<std::vector<State>> ReadBoardFile(std::string path)
{
    std::ifstream file(path);
    std::vector<std::vector<State>> boardvariable;
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<State> row = ParseBoardFile(line);
            boardvariable.push_back(row);
        }
    }
    return boardvariable;
}

bool Compare(const std::vector<int> node_1, const std::vector<int> node_2)
{
    int f1 = node_1[2] + node_1[3];
    int f2 = node_2[2] + node_2[3];
    return f1 > f2;
}

void CellSort(std::vector<std::vector<int>> *v)
{
    std::sort(v->begin(), v->end(), Compare);
}

std::string CellString(State cell)
{
    switch (cell)
    {
        case State::kObstacle: return "⛰️  ";
        case State::kPath: return "🚗  ";
        case State::kStart: return "🚦  ";
        case State::kFinish: return "🏁  ";
        default: return "0   ";
    }
}

bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid)
{
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && y < grid[0].size());
    if(on_grid_x && on_grid_y)
    {
        return grid[x][y] == State::kEmpty;
    }
    return false;
}

void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &open_nodes, std::vector<std::vector<State>> &grid)
{
    open_nodes.push_back(std::vector<int> {x, y, g, h});
    grid[x][y] = State::kClosed;
}

int Heuristic(int x_1, int y_1, int x_2, int y_2)
{
    return std::abs(x_2 - x_1) + std::abs(y_2 - y_1);
}

void ExpandNeighbors(const std::vector<int> &current, int goal[2], std::vector<std::vector<int>> &openlist, std::vector<std::vector<State>> &grid)
{
    int x = current[0];
    int y = current[1];
    int g = current[2];

    for (int i = 0; i < 4; i++)
    {
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];

        if (CheckValidCell(x2, y2, grid))
        {
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, openlist, grid);
        }
    }
}


std::vector<std::vector<State>> Search(std::vector<std::vector<State>> board, int init[2], int goal[2])
{
    std::vector<std::vector<int>> open {};

    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0],goal[1]);
    AddToOpen(x, y, g, h, open, board);

    while (open.size() > 0) {
        CellSort(&open);
        auto current = open.back();
        open.pop_back();
        x = current[0];
        y = current[1];
        board[x][y] = State::kPath;

        if (x == goal[0] && y == goal[1]) {
            board[init[0]][init[1]] = State::kStart;
            board[goal[0]][goal[1]] = State::kFinish;
            return board;
        }
        ExpandNeighbors(current, goal, open, board);
    }

    std::cout << "No path found!" << '\n';
    return std::vector<std::vector<State>> {};
}

void PrintBoardFile(const std::vector<std::vector<State>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            std::cout << CellString(board[i][j]);
        }
        std::cout << '\n';
    }
}


int main() {

    int init[2] {0, 0};
    int goal[2] {5, 6};
    auto board = ReadBoardFile("board");

    auto solution = Search(board, init, goal);

    PrintBoardFile(solution);

    return 0;
}
