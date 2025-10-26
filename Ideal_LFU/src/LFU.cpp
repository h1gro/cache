#include <iostream>
#include <vector>

#include "../include/LFU.hpp"

int main()
{
    int data_elem = 0, future_data_elem = 0;
    size_t cache_size = 0, data_size = 0, future_data_size = 0;
    //std::cout << "Enter cache size and data size" << std::endl;
    std::cin  >> cache_size >> data_size;
    //std::cout << "Enter data:" << std::endl;

    std::vector<int> data        = {};
    std::vector<int> future_data = {};

    for (size_t i = 0; i < data_size; i++)
    {
        std::cin >> data_elem;
        data.push_back(data_elem);
    }
    //TODO input ideal cache
    cache_t<int, int> cache {cache_size};

    std::cout << "CACHE_SIZE = " << cache.cache_size << std::endl;

    cache.filling_cache(data, data.size(), LFU_FREQ);
    cache.print_list();

    std::cout << "hits:" << cache.hits << " misses:" << cache.misses << std::endl
              << "list size: " << cache.cache_list.size() << " hash size: " << cache.hash.size() << std::endl;

    std::cin >> future_data_size;

    for (size_t i = 0; i < future_data_size; i++)
    {
        std::cin >> future_data_elem;
        future_data.push_back(future_data_elem);
    }

    cache.filling_cache(data, data.size(), IDEAL);
    cache.print_list();

    std::cout << "hits:" << cache.hits << " misses:" << cache.misses << std::endl
              << "list size: " << cache.cache_list.size() << " hash size: " << cache.hash.size() << std::endl;
    
    return 0;
}
