#include <iostream>
#include <vector>

#include "../include/LFU.hpp"

int main()
{
    int future_data_elem = 0;
    size_t cache_size = 0, future_data_size = 0;
    std::cin >> cache_size >> future_data_size;

    std::vector<int> future_data = {};

    cache_t<int, int> cache {cache_size};

    for (size_t i = 0; i < future_data_size; i++)
    {
        std::cin >> future_data_elem;
        future_data.push_back(future_data_elem);
    }

    cache.filling_cache(future_data, future_data.size());

    std::cout << cache.hits << std::endl;

    return 0;
}
