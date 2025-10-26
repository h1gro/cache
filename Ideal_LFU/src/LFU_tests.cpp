#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "../include/LFU.hpp"

TEST(CacheTest, Constructor)
{
    cache_t<int, int> cache {3};

    EXPECT_EQ(cache.cache_list.size(), 0);
    EXPECT_EQ(cache.hash.size(), 0);
}

TEST(CacheTest, HitsMisses1)
{
    cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 4, 1, 1};

    cache.filling_cache(data, data.size(), LFU_FREQ);

    EXPECT_EQ(cache.cache_list.size(), 3);
    EXPECT_EQ(cache.hash.size(), 3);
    EXPECT_EQ(cache.hits, 1);
    EXPECT_EQ(cache.misses, 5);
}

TEST(CacheTest, HitsMisses2)
{
    cache_t<int, int> cache {2};
    std::vector<int> data = {1, 1, 1};

    cache.filling_cache(data, data.size(), LFU_FREQ);

    EXPECT_EQ(cache.cache_list.size(), 1);
    EXPECT_EQ(cache.hash.size(), 1);
    EXPECT_EQ(cache.hits, 2);
    EXPECT_EQ(cache.misses, 1);
}

TEST(CacheTest, HitsMisses3)
{
    cache_t<int, int> cache {3};
    std::vector<int> data = {3, 6, 2, 2};

    cache.filling_cache(data, data.size(), LFU_FREQ);

    EXPECT_EQ(cache.cache_list.size(), 3);
    EXPECT_EQ(cache.hash.size(), 3);
    EXPECT_EQ(cache.hits, 1);
    EXPECT_EQ(cache.misses, 3);
}

TEST(CacheTest, HitsMisses4)
{
    cache_t<int, int> cache {4};
    std::vector<int> data = {1, 1, 2, 3, 4,
                             5, 3, 4, 5, 3,
                             3, 6, 1, 2, 1};

    cache.filling_cache(data, data.size(), LFU_FREQ);

    EXPECT_EQ(cache.cache_list.size(), 4);
    EXPECT_EQ(cache.hash.size(), 4);
    EXPECT_EQ(cache.hits, 6);
    EXPECT_EQ(cache.misses, 9);
}
