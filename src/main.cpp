#include <iostream>
#include <iterator>
#include <vector>

#include "../include/cache.h"

int main()
{
    size_t size = 0;
    std::cin >> size;

    cache_t<int> cache {size};

    ReadTests(cache);

    //std::cout << "The program has finished!" << std::endl;
//     std::vector<int> data = {1, 2, 1, 1, 2, 2};
//
//     cache.filling_cache(data, data.size());
//
//     cache.print_list();

    return 0;
}
