#include <iostream>

class MinStack
{
private:
    struct Node
    {
        Node *next;
        int value;
        int min_value;

        Node(int _value, int _min_value, Node *_next)
        {
            next = _next;
            value = _value;
            min_value = _min_value;
        }
    };
    Node *head = nullptr;

public:
    void push(int value)
    {
        if (!head)
        {
            head = new Node(value, value, nullptr);
            return;
        }

        int min_elem = value < head->min_value ? value : head->min_value;
        Node *new_node = new Node(value, min_elem, head);
        head = new_node;
    }

    void pop()
    {
        Node *new_head = head->next;
        head->next = nullptr;
        head = new_head;
    }

    int min()
    {
        return head->min_value;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);

    MinStack stack;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int command;
        std::cin >> command;

        if (command == 1)
        {
            int value;
            std::cin >> value;
            stack.push(value);
        }
        if (command == 2)
        {
            stack.pop();
        }
        if (command == 3)
        {
            std::cout << stack.min() << std::endl;
        }
    }
    return 0;
}