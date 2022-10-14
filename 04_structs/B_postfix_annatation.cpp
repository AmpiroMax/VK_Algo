#include <iostream>
#include <string>

class MyVector
{
private:
    const int INIT_CAPACITY = 8;
    int size;
    int capacity;
    int *data;

public:
    MyVector()
    {
        size = 0;
        capacity = INIT_CAPACITY;
        data = new int[capacity];
    }

    void push_back(int value)
    {
        if (size + 1 > capacity)
        {
            capacity *= 2;
            rewrite_array();
        }
        data[size++] = value;
    }

    int pop_back()
    {
        if (size <= 0)
            throw std::out_of_range("error");

        int result = data[--size];

        if ((capacity > INIT_CAPACITY) && (size < capacity / 4))
        {
            capacity /= 2;
            rewrite_array();
        }

        return result;
    }

    void rewrite_array()
    {
        int *new_array = new int[capacity];

        for (int i = 0; i < size; ++i)
            new_array[i] = data[i];

        delete[] data;
        data = new_array;
        new_array = nullptr;
    }

    ~MyVector()
    {
        delete[] data;
    }
};

int main()
{
    MyVector numbers;
    std::string commands;
    std::getline(std::cin, commands);

    for (int i = 0; i < commands.size(); ++i)
    {
        if (commands[i] == ' ')
            continue;

        if (commands[i] >= '0' && commands[i] <= '9')
        {
            numbers.push_back(commands[i] - '0');
            continue;
        }

        int right_elem = numbers.pop_back();
        int left_elem = numbers.pop_back();

        if (commands[i] == '+')
            numbers.push_back(left_elem + right_elem);
        else if (commands[i] == '-')
            numbers.push_back(left_elem - right_elem);
        else
            numbers.push_back(left_elem * right_elem);
    }

    std::cout << numbers.pop_back() << std::endl;
    return 0;
}