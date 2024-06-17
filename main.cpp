#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>


enum class State {
    kEmpty,
    kObstacle
};

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

std::string CellString(State cell)
{
    switch (cell)
    {
        case State::kObstacle: return "⛰️  ";
        default: return "0   ";
    }
}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> board, int init[2], int goal[2])
{
    std::cout << "No path found!" << '\n';
    return std::vector<std::vector<State>> {};
}

int Heuristic(int x_1, int y_1, int x_2, int y_2)
{
    return std::abs(x_2 - x_1) + std::abs(y_2 - y_1);
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

    auto board = ReadBoardFile("board");
    int init[2] {0, 0};
    int goal[2] {4, 5};

    auto solution = Search(board, init, goal);

    PrintBoardFile(solution);

    return 0;
}
