#include <iostream>
#include <vector>

#include "../include/LFU.hpp"

int main()
{
    int data_elem = 0;
    size_t cache_size = 0, data_size = 0;
    std::cin >> cache_size >> data_size;

    std::vector<int> data = {};

    for (size_t i = 0; i < data_size; i++)
    {
        std::cin >> data_elem;
        data.push_back(data_elem);
    }

    cache_t<int, int> cache {cache_size};

    cache.filling_cache(data, data.size());

    std::cout << cache.hits << std::endl;
    return 0;
}
