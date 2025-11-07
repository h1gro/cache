#ifndef LFU
#define LFU

#include <iostream>
#include <list>
#include <unordered_map>

const int INIT_FREQ = 1000;

template <typename type, typename key_type = int >
struct cache_t
{
    struct list_elem_t
    {
        type elem;
        int frequency;
    };

    size_t cache_size, hits = {0}, misses = {0};

    std::list<list_elem_t> cache_list;

    using list_it = typename std::list<list_elem_t>::iterator;
    std::unordered_map<key_type, list_it> hash;

    cache_t(size_t size) : cache_size(size), cache_list(), hash()
    {
        hash.reserve(size);
    };

    bool cache_full    ();
    void print_list    ();
    auto find_low_freq ();

    void look_up_update (type element);
    void filling_cache  (std::vector<type> data, size_t data_size);

    key_type slow_get_page(type element);
};

template <typename type, typename key_type>
auto cache_t<type, key_type>::find_low_freq()
{
    auto low_freq_it  = cache_list.begin();
    int min_frequency = INIT_FREQ;
    for (auto it = low_freq_it; it != cache_list.end(); it++)
    {
        if (min_frequency >= it->frequency)
        {
            min_frequency = it->frequency;
            low_freq_it   = it;
        }
    }
    return low_freq_it;
}

template <typename type, typename key_type>
void cache_t<type, key_type>::filling_cache(std::vector<type> data, size_t data_size)
{
    for (size_t i = 0; i < data_size; i++)
    {
        look_up_update(data[i]);
    }
}

template <typename type, typename key_type>
key_type cache_t<type, key_type>::slow_get_page(type element)
{
    return element;
}

template <typename type, typename key_type>
void cache_t<type, key_type>::look_up_update(type element)
{
        //print_list();
        auto hash_it = hash.find(slow_get_page(element));

        if (hash_it == hash.end())
        {
            misses++;

            if (cache_full())
            {
                auto list_element = find_low_freq();
                hash.erase(slow_get_page(list_element->elem));

                list_element->elem      = element;
                list_element->frequency = 0;
                hash.emplace(slow_get_page(element), list_element);
            }

            else
            {
                list_elem_t new_element = {element, 0};
                cache_list.push_front(new_element);
                hash.emplace(slow_get_page(element), cache_list.begin());
            }

            //print_list();
        }

        else
        {
            hits++;
            (hash_it->second->frequency)++;
            //print_list();
        }
}

template <typename type, typename key_type>
bool cache_t<type, key_type>::cache_full()
{
    size_t node_number = 0;
    for (auto it = cache_list.begin(); it != cache_list.end() && node_number < cache_size; it++)
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
    for (auto it = cache_list.begin(); it != cache_list.end(); it++)
    {
        if (it == cache_list.begin())
        {
            std::cout << it->elem;
        }
        else
        {
            std::cout << " <-> " << it->elem;
        }
    }
    std::cout << std::endl;
}

#endif
