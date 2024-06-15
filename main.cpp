#include <iostream>
#include <string>
#include <fstream>

void ReadBoardFile(std::string path)
{
    std::ifstream file(path);
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << '\n';
        }
    }
}


int main() {

    ReadBoardFile("board");
    return 0;
}
