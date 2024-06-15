//
// Created by Frederick Lofthouse on 15.06.24.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<int> ParseBoardFile(std::string line)
{
    std::istringstream boardstream(line);
    int number;
    char character;
    std::vector<int> row;

    while (boardstream >> number)
    {
        row.push_back(number);
        if (!(boardstream >> character)) {
            break;
        }
    }
    return row;
}

std::vector<std::vector<int>> ReadBoardFile(const std::string& path)
{
    std::ifstream file(path);
    std::vector<std::vector<int>> boardvariable;
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<int> row = ParseBoardFile(line);
            boardvariable.push_back(row);
        }
    }
    else
    {
        std::cerr << "Failed to open the file: " << path << std::endl;
    }
    return boardvariable;
}

void PrintBoardFile(const std::vector<std::vector<int>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            std::cout << board[i][j];
            if (j < board[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
}

int main() {
    auto board = ReadBoardFile("board");
    PrintBoardFile(board);
    return 0;
}
