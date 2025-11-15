#ifndef LFU
#define LFU

#include <iostream>
#include <list>
#include <unordered_map>
#include <stack>

enum use_t
{
    USED     = 1,
    NOT_USED = 0,
};

const int INIT_FREQ = 1000;

template <typename type, typename key_type = int >
struct cache_t
{
    struct list_elem_t
    {
        type elem;
        int frequency;
        use_t use_id;
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

    bool cache_full    ();
    void print_list    ();

    auto find_not_used ();
    auto find_low_freq ();

    void look_up_update (std::vector<type> data, size_t iterator);
    void filling_cache  (std::vector<type> data, size_t data_size);

    auto ideal_cache_algorithm (std::vector<type> data, size_t current_data_it);

    key_type slow_get_page (type element);
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
        look_up_update(data, i); 
    }
}

template <typename type, typename key_type>
key_type cache_t<type, key_type>::slow_get_page(type element)
{
    return element;
}

template <typename type, typename key_type>
auto cache_t<type, key_type>::ideal_cache_algorithm(std::vector<type> data, size_t current_data_it)
{
    //функция принимает в аргуентах будущую data, итератор data, на котором произошёл miss, c него начнется поиск эл-ов, совпадающих с эл-ами кэша
    size_t number_of_used_cache_elements = 0;
    auto candidate = cache_list.begin();

    //запускаем цикл на поиск элементов кэша, которые встретятся в будущей data.
    //перебираем элементы даты
    for (size_t data_it = current_data_it, data_end_it = data.size(); data_it < data_end_it; data_it++)
    {
        //перебираем элементы кэша, для фиксированного элемента даты
        for (auto list_it = cache_list.begin(), list_end_it = cache_list.end(); list_it != list_end_it; list_it++)
        {
            //TODO сравнение в общем случае, для разных типов

            //если в кэше присутсвует элемент который встретится в data, но мы кладём этот элемент кэша в стэк (если встретили его впервые),
            //для того, чтобы можно было доставать последний элемент очень просто
            if ((list_it->use_id == NOT_USED) && (list_it->elem == data[data_it]))
            {
                cache_stack.push(list_it);

                candidate       = list_it;
                list_it->use_id = USED;

                number_of_used_cache_elements++;
                break;
            }
        }
    }

    //если не все элементы кэша были найдены в будущей data, то существует элемент, который не встретится,
    //а значит его можно удалить из кэша в текущем запросе (если такой элемент не единственный, то удаляем первый такой)
    if (cache_stack.size() != cache_list.size())
    {
        candidate = find_not_used();
    }

    //если все элементы кэша были найдены в будущей дате, то нужно удалять из кэша, тот элемент,
    //который встретится позже остальных, такой элемент лежит на поверхности стека, тк в стек мы элементы
    //клали в порядке их нахождения в дате от её начала до конца
    else
    {
        candidate = cache_stack.top();
    }

    //очистка стека и выставление всех идентификаторов использования (use_id) элементов кэша в NOT_USED
    while (!cache_stack.empty())
    {
        auto list_elem = cache_stack.top();
        list_elem->use_id = NOT_USED;
        cache_stack.pop();
    }

    return candidate;
}

template <typename type, typename key_type>
auto cache_t<type, key_type>::find_not_used()
{
    for (auto list_it = cache_list.begin(), list_end = cache_list.end(); list_it != list_end; list_it++)
    {
        if (list_it->use_id == NOT_USED)
        {
            return list_it;
        }
    }

    std::cerr << "Error in finding unused element in cache!" << std::endl;
    return cache_list.begin();
}

template <typename type, typename key_type>
void cache_t<type, key_type>::look_up_update(std::vector<type> data, size_t iterator)
{
        //print_list();
        bool element_is_the_only_one = true;
        auto hash_it = hash.find(slow_get_page(data[iterator]));

        if (hash_it == hash.end())
        {
            misses++;

            if (cache_full())
            {
                list_it list_element;

                for (size_t next_data_it = iterator + 1, data_end_it = data.size(); next_data_it < data_end_it; next_data_it++)
                {
                    if (data[next_data_it] == data[iterator])
                    {
                        //элемент даты ещё как минимум один раз встретится в дате
                        element_is_the_only_one = false;
                        break;
                    }
                }

                if (!element_is_the_only_one)
                {
                    list_element = ideal_cache_algorithm(data, iterator);

                    hash.erase(slow_get_page(list_element->elem));

                    list_element->elem      = data[iterator];
                    list_element->frequency = 0;
                    hash.emplace(slow_get_page(data[iterator]), list_element);
                }
            }

            else
            {
                list_elem_t new_element = {data[iterator], 0, NOT_USED};
                cache_list.push_front(new_element);
                hash.emplace(slow_get_page(data[iterator]), cache_list.begin());
            }
        }

        else
        {
            hits++;
            (hash_it->second->frequency)++;
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
