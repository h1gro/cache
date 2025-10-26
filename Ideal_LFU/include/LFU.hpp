#ifndef LFU
#define LFU

#include <iostream>
#include <list>
#include <unordered_map>
#include <stack>

enum cache_mode_t
{
    LFU_FREQ = 1,
    IDEAL    = 2,
};

template <typename type, typename key_type = int >
struct cache_t
{
    //todo key_type = type
    struct list_elem_t
    {
        type elem;
        int frequency;
    };

    size_t cache_size, hits = {0}, misses = {0};

    std::list <list_elem_t>  cache_list;

    using list_it = typename std::list<list_elem_t>::iterator;
    std::unordered_map<key_type, list_it> hash;
    std::stack<list_it> cache_stack;

    cache_t(size_t size) : cache_size(size), cache_list(), hash()
    {
        hash.reserve(size);
    };

    bool cache_full();
    void print_list();
    auto find_low_freq();
    void look_up_update(std::vector<type> data, type element, size_t data_size, cache_mode_t mode);
    void filling_cache(std::vector<type> data, size_t data_size, cache_mode_t mode);
    auto ideal_cache_algorithm(std::vector<type> data);
    key_type slow_get_page(type element);
};

template <typename type, typename key_type>
auto cache_t<type, key_type>::find_low_freq()
{
    //std::cout << "--------------------------------" << std::endl;
    auto low_freq_it  = cache_list.begin();
    int min_frequency = 1000; //TODO magic const + test function on debug
    for (auto it = low_freq_it; it != cache_list.end(); it++)
    {
        //std::cout << "elem = " << it->elem << " freq = " << it->frequency << std::endl;
        if (min_frequency >= it->frequency)
        {
            //std::cout << "!!!get new minimum: " << it->frequency << std::endl;
            min_frequency = it->frequency;
            low_freq_it   = it;
        }
    }
    //std::cout << "--------------------------------" << std::endl;
    return low_freq_it;
}

template <typename type, typename key_type>
void cache_t<type, key_type>::filling_cache(std::vector<type> data, size_t data_size, cache_mode_t mode)
{
    for (size_t i = 0; i < data_size; i++)
    {
        look_up_update(data, data[i], data_size, mode);
    }
}

template <typename type, typename key_type>
key_type cache_t<type, key_type>::slow_get_page(type element)
{
    return element;
}

template <typename type, typename key_type>
auto cache_t<type, key_type>::ideal_cache_algorithm(std::vector<type> data)
{
    bool element_found_id = false;

    for (auto list_it = cache_list.begin(), list_end_it = cache_list.end(); list_it != list_end_it; list_it++)
    {
        element_found_id = false;

        for (int data_it = 0, data_end_it = data.size(); data_it < data_end_it; data_it++)
        {
            //TODO сравнение в общем случае, для разных типов
            //TODO случай, когда в кэше первый элемент не совпадает с future data, но в кэше ещё есть элементы, которые будут совпадать
            if (list_it->elem == data[data_it])
            {
                cache_stack.push(list_it);

                element_found_id = true;
                break;
            }
        }

        if (!element_found_id)
        {
            return list_it;
        }

    }

    auto element = cache_stack.top();
    cache_stack.pop();
    return element;
}

template <typename type, typename key_type>
void cache_t<type, key_type>::look_up_update(std::vector<type> data, type element, size_t data_size, cache_mode_t mode)
{
        print_list();
        std::cout << "elem: " << element << std::endl;
        auto hash_it = hash.find(slow_get_page(element));

        if (hash_it == hash.end())
        {
            misses++;
            std::cout << "misses:" << misses << std::endl;

            if (cache_full())
            {
                std::cout << "in" << std::endl;
                list_it list_element;

                if (mode == LFU_FREQ)
                    list_element = find_low_freq();
                else
                    list_element = ideal_cache_algorithm(data);

                std::cout << "find_low_freq: " << list_element->elem << std::endl;
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

            print_list();
            std::cout << std::endl;
        }

        else
        {
            hits++;
            std::cout << "hits:" << hits << std::endl;
            std::cout << std::endl;
            (hash_it->second->frequency)++;
            std::cout << "hit freq = " << hash_it->second->frequency << std::endl;
            print_list();
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

    //std::cout << "node number = " << node_number << std::endl;

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
            std::cout << it->elem;
        }
        else
        {
            std::cout << " <-> " << it->elem;
        }
    }
    std::cout << std::endl;
    //std::cout << ":tail" << std::endl;
}

#endif
