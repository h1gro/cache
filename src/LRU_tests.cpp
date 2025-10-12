#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "../include/LRU.hpp"

TEST(CacheTest, Constructor)
{
    cache_t<int, int> cache {3};

    EXPECT_EQ(cache.cache_list.size(), 0);
    EXPECT_EQ(cache.hash.size(), 0);
}

TEST(CacheTest, HittsMisses1)
{
    cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 4, 1, 1};

    cache.filling_cache(data, data.size());

    EXPECT_EQ(cache.cache_list.size(), 3);
    EXPECT_EQ(cache.hash.size(), 3);
    EXPECT_EQ(cache.hits, 1);
    EXPECT_EQ(cache.misses, 5);
}

TEST(CacheTest, HittsMisses2)
{
    cache_t<int, int> cache {2};
    std::vector<int> data = {1, 1, 1};

    cache.filling_cache(data, data.size());

    EXPECT_EQ(cache.cache_list.size(), 1);
    EXPECT_EQ(cache.hash.size(), 1);
    EXPECT_EQ(cache.hits, 2);
    EXPECT_EQ(cache.misses, 1);
}

TEST(CacheTest, HittsMisses3)
{
    cache_t<int, int> cache {3};
    std::vector<int> data = {3, 6, 2, 2};

    cache.filling_cache(data, data.size());

    EXPECT_EQ(cache.cache_list.size(), 3);
    EXPECT_EQ(cache.hash.size(), 3);
    EXPECT_EQ(cache.hits, 1);
    EXPECT_EQ(cache.misses, 3);
}
