#include <iostream>
#include <string>

class MyVector
{
private:
    int head;
    int tail;
    int capacity;
    int *array;

public:
    MyVector()
    {
        head = 0;
        tail = 0;
        capacity = 8;
        array = new int[capacity];
    }

    void push(int value)
    {
        if (get_size() + 2 > capacity)
        {
            capacity *= 2;
            rewrite_array();
        }
        array[tail] = value;
        tail = (tail + 1) % capacity;
    }

    int pop()
    {
        int rez = array[head];
        head = (head + 1) % capacity;

        if ((capacity > 8) && (get_size() < capacity / 4))
        {
            capacity /= 2;
            rewrite_array();
        }

        return rez;
    }

    void rewrite_array()
    {
        int *new_array = new int[capacity];
        int k = head;
        for (int i = 0; i < get_size(); ++i)
        {
            new_array[i] = array[k];
            k = (k + 1) % capacity;
        }

        delete[] array;
        array = new_array;
        new_array = nullptr;
    }

    int get_size() { return (capacity + tail - head) % capacity; }

    ~MyVector()
    {
        delete[] array;
    }
};

int main()
{
    MyVector queue;
    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i)
    {
        char command;
        std::cin >> command;

        if (command == '+')
        {
            int value;
            std::cin >> value;
            queue.push(value);
        }
        else
        {
            std::cout << queue.pop() << std::endl;
        }
    }

    return 0;
}