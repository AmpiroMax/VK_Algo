#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Heap
{
private:
    vector<pair<int, int>> heap;

    void sift_up(int index)
    {
        int parent = (index - 1) / 2;
        while ((index > 0) && heap[index] < heap[parent])
        {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void sift_down()
    {
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        int index = 0;
        int child = 2 * index + 1;
        while (child < heap.size())
        {
            if ((child + 1 < heap.size()) && heap[child + 1] < heap[child])
                child++;

            if (heap[child] < heap[index])
            {
                swap(heap[index], heap[child]);
                index = child;
                child = 2 * index + 1;
            }
            else
            {
                break;
            }
        }
    }

public:
    void push(int value, int index)
    {
        heap.push_back({value, index});
        sift_up(heap.size() - 1);
    }
    pair<int, int> extract_min()
    {
        if (heap.empty())
            return {-1, -1};

        pair<int, int> min_elem = heap[0];
        sift_down();
        return min_elem;
    }
    void decrease_key(int index, int value)
    {
        int i = 0;
        while (heap[i].second != index)
            i++;
        heap[i].first = value;
        sift_up(i);
    }
};

int main()
{
    Heap priority_queue;
    string command;
    for (int operation_num = 1; cin >> command; ++operation_num)
    {
        if (command == "push")
        {
            int value;
            cin >> value;
            priority_queue.push(value, operation_num);
        }
        if (command == "extract-min")
        {
            pair<int, int> min_elem = priority_queue.extract_min();
            if (min_elem.second == -1)
                cout << "*" << endl;
            else
                cout << min_elem.first << " " << min_elem.second << endl;
        }
        if (command == "decrease-key")
        {
            int iter_num;
            int value;
            cin >> iter_num >> value;
            priority_queue.decrease_key(iter_num, value);
        }
    }

    return 0;
}