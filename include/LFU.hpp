#ifndef LFU
#define LFU

#include <iostream>
#include <list>
#include <unordered_map>

template <typename type, typename key_type>
struct cache_t
{
    struct list_elem_t
    {
        type elem;
        int frequency;
    };

    size_t cache_size, hits, misses;

    std::list<list_elem_t> cache_list;

    using list_it = typename std::list<list_elem_t>::iterator;
    std::unordered_map<key_type, list_it> hash;

    cache_t(size_t size) : cache_size(size), cache_list(), hash()
    {
        hash.reserve(size);
    };

    bool cache_full();
    void print_list();
    void filling_cache(std::vector<type> data, size_t data_size);
    auto find_low_freq();
};

template <typename type, typename key_type>
auto cache_t<type, key_type>::find_low_freq()
{
    auto low_freq_it  = cache_list.begin();
    int min_frequency = 1000; //TODO magic const + test function on debug
    for (auto it = low_freq_it; it != cache_list.end(); it++)
    {
        if (min_frequency > (*it).frequency)
        {
            min_frequency = (*it).frequency;
            low_freq_it = it;
        }
    }

    return low_freq_it;
}

template <typename type, typename key_type>
void cache_t<type, key_type>::filling_cache(std::vector<type> data, size_t data_size)
{
    for (size_t i = 0; i < data_size; i++)
    {
        auto hash_it = hash.find(data[i]);

        if (hash_it == hash.end())
        {
            misses++;
            list_elem_t new_element = {data[i], 0};
            cache_list.push_front(new_element);
            hash.insert({data[i], cache_list.begin()});

            if (cache_full())
            {
                auto list_it = find_low_freq();
                (*list_it).elem      = data[i];
                (*list_it).frequency = 0;
            }
        }
        
        else
        {
            hits++;
            (*(hash_it->second)).frequency++;
        }
    }
}

template <typename type, typename key_type>
bool cache_t<type, key_type>::cache_full()
{
    size_t node_number = 0;
    for (auto it = cache_list.begin(); it != cache_list.end(); it++)
    {
        node_number++;
    }

    if (node_number == cache_size)
    {
        return true;
    }

    return false;
}

template <typename type, typename key_type>
void cache_t<type, key_type>::print_list()
{
    //std::cout << "head:";
    for (auto it = cache_list.begin(); it != cache_list.end(); it++)
    {
        if (it == cache_list.begin())
        {
            std::cout << (*it).elem;
        }
        else
        {
            std::cout << " <-> " << (*it).elem;
        }
    }
    std::cout << std::endl;
    //std::cout << ":tail" << std::endl;
}

#endif
