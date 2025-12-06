#include <fstream>
#include <vector>
#include <array>
#include <chrono>
#include <utility>
#include <iostream>
#include <string>

using Grid = std::vector<std::vector<bool>>;
Grid ConstructGrid(std::ifstream& inf)
{
    std::string line{};
    Grid grid{};
    int row{0};

    while (std::getline(inf, line))
    {
        grid.push_back(std::vector<bool>{});
        for(char ch : line)
        {
            if (ch == '@')
            {
                grid[row].push_back(true);
            }
            else
                grid[row].push_back(false);
        }
        ++row;
    }
    return grid;
}

int CheckIndex(int y, int x, Grid& grid, std::size_t rows, std::size_t cols)
{
    constexpr std::array<std::array<int, 2>, 8> directions {{{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {-1,-1}, {1,-1}, {-1,1}}};
    int neighbors{0};

    for (auto iter : directions)
    {
        auto offset_x{(x + iter[0])};
        auto offset_y{(y + iter[1])};

        if (offset_x < 0 || offset_y < 0 || offset_x >= cols || offset_y >= rows)
            continue;

        
        if (grid[static_cast<std::size_t>(offset_y)][static_cast<std::size_t>(offset_x)] == true)
            ++neighbors;
    }

    if(neighbors >= 4)
        return 0;

    grid[y][x] = false;
    return 1;
}

int main()
{
    std::ifstream inf {"./input.txt"};
    if (!inf)
    {
        std::cerr << "Could not open file.\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long sum{0};
    
    auto grid = std::move(ConstructGrid(inf));

    bool change_happened{true};
    while(change_happened)
    {
        change_happened = false;
        for (int i {0}; i < grid.size(); ++i)
    {
        for (int j{0}; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == true)
            {
                auto result = CheckIndex(i, j, grid, grid.size(), grid[0].size());
                if (result == 1)
                    change_happened = true;
                sum += result;
            }
        }
    }
    }
    


    std::cout << sum << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}
