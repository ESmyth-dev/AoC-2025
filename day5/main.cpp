#include <fstream>
#include <array>
#include <chrono>
#include <unordered_set>
#include <iostream>
#include <string>

int main()
{
    std::ifstream inf {"./input.txt"};
    if (!inf)
    {
        std::cerr << "Could not open file.\n";
        return 1;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    std::string line{};
    unsigned long long sum{0};
    std::vector<std::pair<unsigned long long , unsigned long long>> fresh_nums{};
    
    while (std::getline(inf, line))
    {
        if (line == "")
            break;
        
        std::size_t delim_index = line.find('-');
        std::string start_str{line.substr(0, delim_index)};
        std::string end_str{line.substr(delim_index+1)};

       unsigned long long start = std::stoll(start_str);
       unsigned long long end = std::stoll(end_str);

        fresh_nums.push_back(std::pair<unsigned long long, unsigned long long>{start, end});
    }

    for (std::size_t i {0}; i < fresh_nums.size(); ++i)
    {
        for (std::size_t j {0}; j < i; ++j)
        {
            if (fresh_nums[j].first > fresh_nums[j].second)
                continue;

            if (fresh_nums[i].first >= fresh_nums[j].first && fresh_nums[i].first <= fresh_nums[j].second)
            {
                fresh_nums[i].first = fresh_nums[j].second + 1;
            }

            if (fresh_nums[i].second >= fresh_nums[j].first && fresh_nums[i].second <= fresh_nums[j].second)
            {
                fresh_nums[i].second = fresh_nums[j].first - 1;
            }

        }
        if (fresh_nums[i].first > fresh_nums[i].second)
            continue;

        std::vector<std::pair<unsigned long long , unsigned long long>>  inner_duplicates{};
        for (std::size_t j {0}; j < i; ++j)
        {
            if (fresh_nums[j].first >= fresh_nums[i].first && fresh_nums[j].first <= fresh_nums[i].second && fresh_nums[j].second >= fresh_nums[i].first && fresh_nums[j].second <= fresh_nums[i].second)
            {
                inner_duplicates.push_back({fresh_nums[j].first, fresh_nums[j].second});
            }
        }

        for (std::size_t i {0}; i < inner_duplicates.size(); ++i)
        {
            for (std::size_t j {0}; j < i; ++j)
            {
                if (inner_duplicates[j].first > inner_duplicates[j].second)
                    continue;

                if (inner_duplicates[i].first >= inner_duplicates[j].first && inner_duplicates[i].first <= inner_duplicates[j].second)
                {
                    inner_duplicates[i].first = inner_duplicates[j].second + 1;
                }

                if (inner_duplicates[i].second >= inner_duplicates[j].first && inner_duplicates[i].second <= inner_duplicates[j].second)
                {
                    inner_duplicates[i].second = inner_duplicates[j].first - 1;
                }

                if (inner_duplicates[j].first >= inner_duplicates[i].first && inner_duplicates[j].first <= inner_duplicates[i].second && inner_duplicates[j].second >= inner_duplicates[i].first && inner_duplicates[j].second <= inner_duplicates[i].second)
                {
                    inner_duplicates[j].first = 2;
                    inner_duplicates[j].second = 1;
                }

            }
        }


        sum += (fresh_nums[i].second - fresh_nums[i].first + 1);
        for (auto pair : inner_duplicates)
        {
            if (pair.first > pair.second)
                continue;

            sum -= (pair.second - pair.first + 1);
        }
    }

    

    std::cout << sum << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start_time);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}
