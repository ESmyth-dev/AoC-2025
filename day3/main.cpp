#include <fstream>
#include <array>
#include <chrono>
#include <iostream>
#include <string>

constexpr int NUM_OF_DIGITS{12};

int main()
{
    std::ifstream inf {"./input2.txt"};
    if (!inf)
    {
        std::cerr << "Could not open file.\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string line{};
    unsigned long long sum{0};

    
    while (std::getline(inf, line))
    {
        std::array<char, NUM_OF_DIGITS> nums{};
        std::fill(nums.begin(), nums.end(), -1);

        std::cout << line << '\n';
        for(std::size_t i{0}; i < line.size(); i++)
        {
            for (std::size_t j{0}; j < nums.size(); ++j)
            {
                if (line[i] > nums[j] && i <= line.size() - (nums.size() - j))
                {
                    nums[j] = line[i];
                    std::fill(nums.begin() + (j + 1), nums.end(), -1);
                    break;
                }
            }
        }
        std::string str_num{};
        for (char ch : nums)
            str_num.push_back(ch);
        unsigned long long num{std::stoull(str_num.c_str())};
        std::cout << num << '\n';
        sum += num;
    }

    std::cout << sum << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}
