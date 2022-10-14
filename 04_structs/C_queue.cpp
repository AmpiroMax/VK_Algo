#include <iostream>
#include <string>

class MyVector
{
private:
    const int INIT_CAPACITY = 8;

    int head;
    int tail;
    int capacity;
    int *data;

public:
    MyVector()
    {
        head = 0;
        tail = 0;
        capacity = INIT_CAPACITY;
        data = new int[capacity];
    }

    void push(int value)
    {
        if (get_size() + 2 > capacity)
        {
            capacity *= 2;
            rewrite_array();
        }
        data[tail] = value;
        tail = (tail + 1) % capacity;
    }

    int pop()
    {
        int result = data[head];
        head = (head + 1) % capacity;

        if ((capacity > INIT_CAPACITY) && (get_size() < capacity / 4))
        {
            capacity /= 2;
            rewrite_array();
        }

        return result;
    }

    void rewrite_array()
    {
        int *new_array = new int[capacity];
        int k = head;
        for (int i = 0; i < get_size(); ++i)
        {
            new_array[i] = data[k];
            k = (k + 1) % capacity;
        }

        delete[] data;
        data = new_array;
        new_array = nullptr;
    }

    int get_size() { return (capacity + tail - head) % capacity; }

    ~MyVector()
    {
        delete[] data;
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