#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>

class HashTable
{
private:
    const int A = 31;
    const int P = 1e9 + 7;
    const int INITIAL_SIZE = 1000;

    struct Data
    {
        std::string key_word;
        std::string value_word;

        Data *next;
        Data *prev;

        Data()
        {
            key_word = "";
            value_word = "";
            next = nullptr;
            prev = nullptr;
        }

        bool operator==(const Data &rhs)
        {
            return key_word == rhs.key_word;
        }
    };

    std::vector<std::list<Data *>> table;
    Data *prev_put;

    size_t hash(const std::string &key_word)
    {
        size_t result = 0;
        for (auto letter : key_word)
        {
            result = (result + (letter - 'a' + 1)) % P;
            result = (result * A) % P;
        }

        return result % table.size();
    }

    std::list<HashTable::Data *>::iterator find_iter(const std::string &key_word)
    {
        size_t index = hash(key_word);
        auto iter = std::find_if(table[index].begin(), table[index].end(), [&key_word](Data *data)
                                 { return data->key_word == key_word; });
        return iter;
    }

public:
    HashTable()
    {
        table = std::vector<std::list<Data *>>(INITIAL_SIZE);
        prev_put = nullptr;
    }

    void put(const std::string &key_word, const std::string &value_word)
    {
        Data *element = new Data;
        element->key_word = key_word;
        element->value_word = value_word;

        size_t index = hash(key_word);
        auto iter = find_iter(key_word);

        if (iter == table[index].end())
        {
            table[index].push_back(element);
            iter = table[index].end();
            iter--;

            (*iter)->prev = prev_put;
            if (prev_put)
                prev_put->next = *iter;

            prev_put = *iter;
        }
        else
        {
            (*iter)->value_word = value_word;
        }
    }

    void delete_element(const std::string &key_word)
    {
        size_t index = hash(key_word);
        auto iter = find_iter(key_word);

        if (iter == table[index].end())
            return;

        if ((*iter) == prev_put)
        {
            prev_put = (*iter)->prev;
        }

        if ((*iter)->next)
            (*iter)->next->prev = (*iter)->prev;

        if ((*iter)->prev)
            (*iter)->prev->next = (*iter)->next;

        (*iter)->next = nullptr;
        (*iter)->prev = nullptr;
        // delete (*iter);

        auto erase_end = iter;
        erase_end++;
        table[index].erase(iter, erase_end);
    }

    std::string get(const std::string &key_word)
    {
        size_t index = hash(key_word);
        auto iter = find_iter(key_word);

        if (iter == table[index].end())
            return "none";

        return (*iter)->value_word;
    }

    std::string prev(const std::string &key_word)
    {
        size_t index = hash(key_word);
        auto iter = find_iter(key_word);

        if (iter == table[index].end())
            return "none";

        if (!(*iter)->prev)
            return "none";

        return (*iter)->prev->value_word;
    }

    std::string next(const std::string &key_word)
    {
        size_t index = hash(key_word);
        auto iter = find_iter(key_word);

        if (iter == table[index].end())
            return "none";

        if (!(*iter)->next)
            return "none";

        return (*iter)->next->value_word;
    }
};

int main()
{
    HashTable my_table;
    std::string command;

    for (; std::cin >> command;)
    {
        std::string key_word;
        std::cin >> key_word;

        if (command == "put")
        {
            std::string value_word;
            std::cin >> value_word;
            my_table.put(key_word, value_word);
        }

        if (command == "get")
            std::cout << my_table.get(key_word) << std::endl;

        if (command == "prev")
            std::cout << my_table.prev(key_word) << std::endl;

        if (command == "next")
            std::cout << my_table.next(key_word) << std::endl;

        if (command == "delete")
            my_table.delete_element(key_word);
    }

    return 0;
}