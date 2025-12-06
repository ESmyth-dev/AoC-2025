#include <fstream>
#include <vector>
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

    std::string line{};
    unsigned long long sum{0};

    
    while (std::getline(inf, line, ','))
    {
        unsigned long long start{std::stoull(line.substr(0, line.find('-')).c_str())};
        unsigned long long end{std::stoull(line.substr(line.find('-') + 1).c_str())};

        for(unsigned long long iter{start}; iter <= end; ++iter)
        {
            std::string str = std::to_string(iter);

            for (int i{1}; i<=(str.size()/2); ++i)
            {
                double num_of_slices_dbl = static_cast<double>(str.size()/static_cast<double>(i));
                if (floor(num_of_slices_dbl) != num_of_slices_dbl)
                    continue;
                
                std::size_t num_of_slices{str.size()/i};

                bool result{true};
                std::string first {str.substr(0, i)};
                for (std::size_t j{1}; j< num_of_slices; ++j)
                {
                    std::string next = str.substr(j*i, i);
                    result = first == next;
                    if (!result)
                        break;
                }

                if (result)
                {
                    sum += iter;
                    break;
                }
            }
        }
    }

    std::cout << sum << '\n';
    return 0;
}
