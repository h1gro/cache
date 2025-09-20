#include <iostream>

#include "../include/cache.h"

int main()
{
    size_t size = 0, data_size = 6;
    std::cin >> size;

    cache_t<int> cache {size};

    init_data();

    int* data = new int[data_size] {1, 2, 1, 1, 2, 2};

    //std::cout << cache.cache_full() << std::endl;

    cache.filling_cache(data, data_size);

    cache.print_list();

    delete [] data;

    return 0;
}
