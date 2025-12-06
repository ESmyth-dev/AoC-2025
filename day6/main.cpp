#include <fstream>
#include <array>
#include <vector>
#include <chrono>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <string>

unsigned long long CompleteOperation(unsigned long long num1, unsigned long long num2, char op)
{
    if (op == '+')
    {
        return num1 + num2;
    }
    else
    {
        return num1 * num2;
    }
}

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
    int line_num{0};
    std::vector<std::string> string_rows{};

    while (std::getline(inf, line))
    {
        string_rows.push_back(line);
    }

    char op {string_rows[string_rows.size()-1][0]};
    std::size_t last_operator_index{0};

    for (std::size_t i{1}; i < string_rows[0].size(); ++i)
    {
        if (string_rows[string_rows.size()-1][i] != ' ' || i == string_rows[0].size()-1)
        {
            if(i == string_rows[0].size()-1)
                i += 2;

            unsigned long long inner_sum{0};
            for (std::size_t j{i - 2}; j >= last_operator_index; --j)
            {
                std::string current_num_str{};
                for (std::size_t k{0}; k < string_rows.size() - 1; ++k)
                {
                    if (string_rows[k][j] == ' ')
                        continue;

                    current_num_str.push_back(string_rows[k][j]);
                }
                if (inner_sum==0)
                    inner_sum = std::stoull(current_num_str);
                else
                    inner_sum = CompleteOperation(inner_sum, std::stoull(current_num_str), op);
                
                if (j == 0)
                    break;
            }

            op = string_rows[string_rows.size() - 1][i];
            last_operator_index = i;
            sum += inner_sum;
        }
    }

    std::cout << sum << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start_time);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;
    return 0;
}
