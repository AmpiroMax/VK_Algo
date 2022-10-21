#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Set
{
private:
    enum Status
    {
        full,
        empty,
        rip
    };

    struct Data
    {
        int key;
        int value;
        Status stat;

        Data()
        {
            key = -1;
            stat = empty;
        }
    };

    const int INITIAL_SIZE = 1000;
    const int P = 1e6 + 3;

    // Задаю максимальное значение для переменной A,
    // используемую для рехеша.
    const int HASH_A_MAX = 50;

    int hash_A;
    int count_filled;
    int count_deleted;

    vector<Data> table;

    void rerand_hash_A() { hash_A = rand() % 50; }

    size_t hash(int key)
    {
        return (hash_A * (size_t(key) % P)) % P % table.size();
    }

    void rehashing(int new_size)
    {
        vector<Data> new_table = vector<Data>(new_size);

        int old_size = table.size();
        table.resize(new_size);

        rerand_hash_A();

        for (int i = 0; i < old_size; ++i)
        {
            Data element = table[i];
            if (element.stat == Status::rip || element.stat == Status::empty)
                continue;

            int index = hash(element.key);
            for (; new_table[index].stat != Status::empty; index = (index + 1) % new_table.size())
                ;

            new_table[index] = element;
        }
        count_filled -= count_deleted;
        count_deleted = 0;
        table = new_table;
    }

public:
    Set()
    {
        table = vector<Data>(INITIAL_SIZE);
        rerand_hash_A();
        count_filled = 0;
        count_deleted = 0;
    }

    void insert(int x)
    {
        if (exists(x))
            return;

        int index = hash(x);
        for (; table[index].stat == Status::full;
             index = (index + 1) % table.size())
            ;

        if (table[index].stat == Status::empty)
            count_filled++;
        else
            count_deleted--;

        table[index].key = x;
        table[index].stat = Status::full;

        if (count_filled + count_deleted >= table.size() / 2)
            rehashing(2 * table.size());
    }

    void delete_element(int x)
    {
        int index = hash(x);
        for (; table[index].stat != Status::empty;
             index = (index + 1) % table.size())
        {
            if (table[index].key == x && table[index].stat == Status::full)
            {
                table[index].stat = Status::rip;
                count_deleted++;

                if (count_filled + count_deleted >= table.size() / 2)
                    rehashing(table.size());
                return;
            }
        }
    }

    bool exists(int x)
    {
        int index = hash(x);
        for (; table[index].stat != Status::empty; index = (index + 1) % table.size())
        {
            if (table[index].key == x && table[index].stat == Status::rip)
                return false;

            if (table[index].key == x && table[index].stat == Status::full)
                return true;
        }
        return false;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    Set my_set;
    string command;
    for (; cin >> command;)
    {
        int element;
        cin >> element;

        if (command == "insert")
            my_set.insert(element);

        if (command == "delete")
            my_set.delete_element(element);

        if (command == "exists")
            cout << (my_set.exists(element) ? "true" : "false") << endl;
    }
    return 0;
}