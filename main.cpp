#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>


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
    PrintBoardFile(board);

    return 0;
}
