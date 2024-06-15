#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>


std::vector<int> ParseBoardFile(std::string line)
{
    std::istringstream boardstream(line);
    int number;
    char character;
    std::vector<int> row;

    while (boardstream >> number >> character && character == ',')
    {
        row.push_back(number);
    }
    return row;
}


std::vector<std::vector<int>> ReadBoardFile(std::string path)
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
    return boardvariable;
}

void PrintBoardFile(const std::vector<std::vector<int>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            std::cout << std::setw(3) << board[i][j] << std::setw(3);
        }
        std::cout << '\n';
    }
}

int main() {


    auto start = std::chrono::high_resolution_clock::now();

    auto board = ReadBoardFile("board");
    PrintBoardFile(board);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;


    return 0;
}