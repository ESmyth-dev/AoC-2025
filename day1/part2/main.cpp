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
    bool lastWasZero{false};
    bool passedZero{false};
    int zeros{0};
    std::string line{};

    
    while (std::getline(inf, line))
    {
        int diff = std::atoi(line.substr(1).c_str());
        std::cout << "Starting at " << startPos << "\n";

        if (line[0] == 'L')
        {
            startPos -= diff;

            while (startPos < 0)
            {
                startPos = 100 + startPos;
                if(!lastWasZero)
                {
                    std::cout << "CROSSED ZERO 1 TIME!\n";
                    ++zeros;
                }
                lastWasZero = false;
            }
            
            std::cout << "Go left by " << diff << " to arrive at " << startPos <<"\n";
        }

        else
        {
            lastWasZero = false;
            startPos += diff;
            while (startPos > 99)
            {
                startPos = startPos - 100;
                std::cout << "CROSSED ZERO 1 TIME!\n";
                ++zeros;
                passedZero = true;
            }

            std::cout << "Go right by " << diff << " to arrive at " << startPos <<"\n";
        }

        if (startPos == 0)
        {
            if (passedZero == false)
            {
                std::cout << "Landed on zero... and it counts!\n";
                ++zeros;
            }
            else
            {
                std::cout << "Landed on zero but it does not count\n";
            }
            
            lastWasZero = true;
        }
        passedZero = false;
    } 

    std::cout << "Landed on zero " << zeros << " times";
    
    
    return 0;
}
