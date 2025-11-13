#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "../include/Ideal_cache.hpp"

TEST(CacheTest, Constructor)
{
    cache_t<int, int> cache {3};

    EXPECT_EQ(cache.cache_list.size(), 0);
    EXPECT_EQ(cache.hash.size(), 0);
}

TEST(CacheTest, IdealHits1)
{
    cache_t<int, int> cache {4};

    std::vector<int> future_data = {1, 2, 3, 4, 1, 2,
                                    5, 1, 2, 4, 3, 4};

    cache.filling_cache(future_data, future_data.size());

    EXPECT_EQ(cache.cache_list.size(), 4);
    EXPECT_EQ(cache.hash.size(), 4);
    EXPECT_EQ(cache.hits, 7);
    EXPECT_EQ(cache.misses, 5);
}

TEST(CacheTest, IdealHits2)
{
    cache_t<int, int> cache {3};

    std::vector<int> future_data = {5, 4, 9, 9, 2,
                                    3, 4, 5, 5, 9};

    cache.filling_cache(future_data, future_data.size());

    EXPECT_EQ(cache.cache_list.size(), 3);
    EXPECT_EQ(cache.hash.size(), 3);
    EXPECT_EQ(cache.hits, 5);
    EXPECT_EQ(cache.misses, 5);
}

TEST(CacheTest, IdealHits3)
{
    cache_t<int, int> cache {3};

    std::vector<int> future_data = {0, 0, 0, 2, 2,
                                    0, 0, 2, 1, 6,
                                    8, 9, 8, 8, 1};

    cache.filling_cache(future_data, future_data.size());

    EXPECT_EQ(cache.cache_list.size(), 3);
    EXPECT_EQ(cache.hash.size(), 3);
    EXPECT_EQ(cache.hits, 9);
    EXPECT_EQ(cache.misses, 6);
}

