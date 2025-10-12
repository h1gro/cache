#include <iostream>
#include <iterator>
#include <vector>

#include "../include/LRU.hpp"

int main() 
{
    int data_elem = 0;
    size_t cache_size = 0, data_size = 0;
    std::cout << "Enter cache size and data size" << std::endl;
    std::cin >> cache_size >> data_size;
    std::cout << "Enter data:" << std::endl;

    std::vector<int> data = {};

    for (size_t i = 0; i < data_size; i++)
    {
        std::cin >> data_elem;
        data.push_back(data_elem);
    }

    cache_t<int, int> cache {cache_size};

    cache.filling_cache(data, data.size());

    return 0;
}

void PrintVector(const std::vector<int>& vec)
{
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;
}
