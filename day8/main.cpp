#include <fstream>
#include <array>
#include <vector>
#include <chrono>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

struct Coordinate
{
    double x;
    double y;
    double z;

    static double DistanceBetweenCoords(Coordinate c1, Coordinate c2)
    {
        return std::sqrt(std::pow(c2.x - c1.x, 2) + std::pow(c2.y - c1.y, 2) + std::pow(c2.z - c1.z, 2));
    }

    bool operator<(const Coordinate& other) const
    {
        return x < other.x;
    }
};

struct Connection
{
    Coordinate coord1;
    Coordinate coord2;
    double distance;

     bool operator<(const Connection& other) const 
     {
        return distance < other.distance;
    }
};

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
    std::vector<Coordinate> coords{};
    std::vector<Connection> connections{};

    while (std::getline(inf, line))
    {
        std::vector<double> coord;
        std::stringstream ss{line};
        std::string chunk;
        while(std::getline(ss, chunk, ','))
        {
            coord.push_back(std::stod(chunk));
        }

        coords.push_back({coord[0], coord[1], coord[2]});
    }

    for (std::size_t i {0}; i < coords.size(); ++i)
    {
        for (std::size_t j {i+1}; j < coords.size(); ++j)
        {
            connections.push_back({coords[i], coords[j], Coordinate::DistanceBetweenCoords(coords[i], coords[j])});
        }
    }

    std::sort(connections.begin(), connections.end(), 
        [](const Connection& c1, const Connection& c2)
    {
        return c1.distance < c2.distance;
    });
    
    std::vector<std::set<Coordinate>> circuits;

    bool inserted{false};
    for (std::size_t i {0}; i < 1000; ++i)
    {
        inserted = false;
        if (circuits.empty())
        {
            circuits.push_back(std::set<Coordinate>{});
            circuits[0].insert(connections[i].coord1);
            circuits[0].insert(connections[i].coord2);
            continue;
        }

        int first_match{-1};
        for (std::size_t j {0}; j < circuits.size(); ++j)
        {
            if (circuits[j].contains(connections[i].coord1))
            {
                inserted = true;
                if (first_match != -1)
                {
                    circuits[first_match].insert(circuits[j].begin(), circuits[j].end());
                    circuits.erase(circuits.begin() + j);
                    break;
                }
                circuits[j].insert(connections[i].coord2);
                first_match = static_cast<int>(j);
            }
            else if (circuits[j].contains(connections[i].coord2))
            {
                inserted = true;
                if (first_match != -1)
                {
                    circuits[first_match].insert(circuits[j].begin(), circuits[j].end());
                    circuits.erase(circuits.begin() + j);
                    break;
                }
                circuits[j].insert(connections[i].coord1);
                first_match = static_cast<int>(j);
            }
        }
        if (inserted)
            continue;

        circuits.push_back(std::set<Coordinate>{});
        circuits[circuits.size()-1].insert(connections[i].coord1);
        circuits[circuits.size()-1].insert(connections[i].coord2);
    }

    std::sort(circuits.begin(), circuits.end(), 
        [](const std::set<Coordinate>& s1, const std::set<Coordinate>& s2)
    {
        return s1.size() > s2.size();
    });

    unsigned long long product{1};

    for (std::size_t i{0}; i<3; ++i)
    {
        product *= circuits[i].size();
    }

    std::cout << product << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start_time);
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;
    return 0;
}
