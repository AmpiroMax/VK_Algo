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
        std::list<std::string> value_words;

        Data()
        {
            key_word = "";
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
        element.value_words.push_back(value_word);

        size_t index = hash(key_word);
        auto iter = std::find_if(table[index].begin(), table[index].end(), [&key_word](Data data) { return data.key_word == key_word; });

        if (iter == table[index].end())
        {
            table[index].push_back(element);
            return;
        }

        auto words_iter = std::find_if(iter->value_words.begin(), iter->value_words.end(),
                                       [&value_word](const std::string &data_word) { return data_word == value_word; });

        if (words_iter == iter->value_words.end())
            iter->value_words.push_back(value_word);
    }

    void delete_pair(const std::string &key_word, const std::string &value_word)
    {
        size_t index = hash(key_word);
        auto iter = std::find_if(table[index].begin(), table[index].end(), [&key_word](Data data) { return data.key_word == key_word; });

        if (iter == table[index].end())
            return;

        auto words_iter = std::find_if(iter->value_words.begin(), iter->value_words.end(),
                                       [&value_word](const std::string &data_word) { return data_word == value_word; });

        if (words_iter == iter->value_words.end())
            return;

        if (iter->value_words.size() == 1)
        {
            auto erase_end = iter;
            erase_end++;
            table[index].erase(iter, erase_end);
            return;
        }

        auto erase_word_end = words_iter;
        erase_word_end++;
        iter->value_words.erase(words_iter, erase_word_end);
    }

    void delete_all(const std::string &key_word)
    {
        size_t index = hash(key_word);
        auto iter = std::find_if(table[index].begin(), table[index].end(), [&key_word](Data data) { return data.key_word == key_word; });

        if (iter == table[index].end())
            return;

        auto erase_end = iter;
        erase_end++;
        table[index].erase(iter, erase_end);
        return;
    }

    void get(const std::string &key_word)
    {
        size_t index = hash(key_word);
        auto iter = std::find_if(table[index].begin(), table[index].end(), [&key_word](Data data) { return data.key_word == key_word; });

        if (iter == table[index].end())
        {
            std::cout << 0 << std::endl;
            return;
        }

        std::cout << iter->value_words.size() << " ";

        for (auto word : iter->value_words)
            std::cout << word << " ";

        std::cout << std::endl;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
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
            my_table.get(key_word);
        }

        if (command == "delete")
        {
            std::string key_word;
            std::string value_word;
            std::cin >> key_word >> value_word;
            my_table.delete_pair(key_word, value_word);
        }

        if (command == "deleteall")
        {
            std::string key_word;
            std::cin >> key_word;
            my_table.delete_all(key_word);
        }
    }

    return 0;
}