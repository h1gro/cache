#include <iostream>
#include <iterator>
#include <vector>

#include "../include/cache.hpp"

int main()
{
    size_t size = 0;
    std::cin >> size;

    cache_t<int, int> cache {size};

    ReadTests(cache);

    return 0;
}


