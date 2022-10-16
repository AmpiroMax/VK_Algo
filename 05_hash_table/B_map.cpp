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
    const int P = 1'000'000'007;
    const int INITIAL_SIZE = 1000;

    struct Data
    {
        std::string key_word;
        std::string value_word;

        Data()
        {
            key_word = "";
            value_word = "";
        }

        bool operator==(const Data &rhs)
        {
            return key_word == rhs.key_word;
        }
    };

    std::vector<std::list<Data>> table;

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

public:
    HashTable()
    {
        table = std::vector<std::list<Data>>(INITIAL_SIZE);
    }

    void put(const std::string &key_word, const std::string &value_word)
    {
        Data element;
        element.key_word = key_word;
        element.value_word = value_word;

        size_t index = hash(key_word);
        auto iter = std::find(table[index].begin(), table[index].end(), element);

        if (iter == table[index].end())
            table[index].push_back(element);
        else
            (*iter).value_word = value_word;
    }

    void delete_element(const std::string &key_word)
    {
        Data element;
        element.key_word = key_word;
        element.value_word = "";

        size_t index = hash(key_word);
        auto iter = std::find(table[index].begin(), table[index].end(), element);

        if (iter == table[index].end())
            return;

        auto erase_end = iter;
        erase_end++;
        table[index].erase(iter, erase_end);
    }

    std::string get(const std::string &key_word)
    {
        Data element;
        element.key_word = key_word;
        element.value_word = "";

        size_t index = hash(key_word);
        auto iter = std::find(table[index].begin(), table[index].end(), element);

        if (iter == table[index].end())
            return "none";

        return (*iter).value_word;
    }
};

int main()
{
    HashTable my_table;
    std::string command;

    for (; std::cin >> command;)
    {
        if (command == "put")
        {
            std::string key_word;
            std::string value_word;
            std::cin >> key_word >> value_word;
            my_table.put(key_word, value_word);
        }

        if (command == "get")
        {
            std::string key_word;
            std::cin >> key_word;
            std::cout << my_table.get(key_word) << std::endl;
        }

        if (command == "delete")
        {
            std::string key_word;
            std::cin >> key_word;
            my_table.delete_element(key_word);
        }
    }

    return 0;
}