#ifndef CACHE
#define CACHE

#include <list>
#include <unordered_map>
#include <assert.h>

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


    void filling_cache(type* data, int data_size)
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

void init_data();

#endif
