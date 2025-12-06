#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream inf {"../input.txt"};
    if (!inf)
    {
        std::cerr << "Could not open file.\n";
        return 1;
    }

    int startPos{50};
    int zeros{0};
    std::string line{};

    
    while (std::getline(inf, line))
    {
        int diff = std::atoi(line.substr(1).c_str());

        std::cout << "Starting at " << startPos << " ";
        if (line[0] == 'L')
        {
            startPos -= diff;

            while (startPos < 0)
            {
                startPos = 100 + startPos;
            }

             std::cout << "Go left by " << diff << " to arrive at " << startPos <<"\n";
        }

        else
        {
            startPos += diff;
            while (startPos > 99)
            {
                startPos = startPos - 100;
            }

            std::cout << "Go right by " << diff << " to arrive at " << startPos <<"\n";
        }

        if (startPos == 0)
        {
            ++zeros;
        }
    } 

    std::cout << "Landed on zero " << zeros << " times";
    
    
    return 0;
}
