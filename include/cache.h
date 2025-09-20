#ifndef CACHE
#define CACHE

#include <list>
#include <unordered_map>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

template <typename type, typename key_type = int >
struct cache_t
{
    size_t cache_size;
    std::list<type> cache_list;

    using list_it = typename std::list<type>::iterator;
    std::unordered_map<key_type, list_it> hash;

    cache_t(size_t size) : cache_size(size) {};

    void print_list()
    {
        //std::cout << "head:";
        for (auto it = cache_list.begin(); it != cache_list.end(); it++)
        {
            if (it == cache_list.begin())
            {
                std::cout << *it;
            }
            else
            {
                std::cout << " <-> " << *it;
            }
        }
        std::cout << std::endl;
        //std::cout << ":tail" << std::endl;
    }


    void filling_cache(std::vector<type> data, int data_size)
    {
        for (int i = 0; i < data_size; i++)
        {
            auto key_node = hash.find(data[i]);

            if (key_node == hash.end())
            {
                if (cache_full())
                {
                    hash.erase(cache_list.back());
                    cache_list.pop_back();
                }

                cache_list.push_front(data[i]);
                hash[data[i]]= cache_list.begin();
            }

            else
            {
                auto node = key_node->second;
                if(node != cache_list.begin())
                {
                    cache_list.splice(cache_list.begin(), cache_list, node, std::next(node));
                }
            }
        }
    }

    bool cache_full()
    {
        int node_number = 0;
        for (auto it = cache_list.begin(); it != cache_list.end(); it++)
        {
            node_number++;
        }

        if (node_number == cache_size)
        {
            return 1;
        }

        return 0;
    }
};

static const char* TESTS_FILE = "tests/tests.txt";

void init_data();
void PrintVector(const std::vector<int>& vec);

template <typename type> void ReadTests(cache_t<type>& cache)
{
    std::string data_line;
    std::string cache_line;
    std::ifstream input_file(TESTS_FILE);

    if (input_file.is_open())
    {
        while ((std::getline(input_file, data_line)) && (std::getline(input_file, cache_line)))
        {
            std::stringstream string_data(data_line);
            std::stringstream string_cache(cache_line);

            std::vector<int> data_test;
            std::vector<int> cache_test;

            int elem_data_test = 0, elem_cache_test = 0;

            while (string_data >> elem_data_test)
            {
                //std::cout << elem_data_test << std::endl;
                data_test.push_back(elem_data_test);
            }

            while (string_cache >> elem_cache_test)
            {
                //std::cout << elem_cache_test << std::endl;
                cache_test.push_back(elem_cache_test);
            }

            cache.filling_cache(data_test, data_test.size());

            auto vector_it = cache_test.begin();
            for (auto it = cache.cache_list.begin(); it != cache.cache_list.end(); it++)
            {
                //std::cout << *it << " ";
                if (*it != *vector_it)
                {
                    std::cout << "ERROR IN TESTS!!!" << std::endl;
                    break;
                }
                vector_it++;
            }

            //PrintVector(data_test);
            //std::cout << "wrote data" << std::endl;
            //PrintVector(cache_test);
            //std::cout << "wrote cache" << std::endl;

            data_test.clear();
            cache_test.clear();

            cache.cache_list.clear();
            cache.hash.clear();
        }
        input_file.close();
    }

    else
    {
        std::cerr << "input file was not open" << std::endl;
    }
}

#endif
