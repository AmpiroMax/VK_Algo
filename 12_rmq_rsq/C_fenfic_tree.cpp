#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print(const vector<int64_t> &vec)
{
    for (auto el : vec)
        cout << el << " ";
    cout << endl;
}

class FenvicTree
{
private:
    vector<int64_t> T;
    vector<int64_t> array;

    int64_t F(int64_t i) { return i & (i + 1); }

    int64_t get(int64_t i)
    {
        int64_t res = 0;
        for (int64_t j = i; j >= 0; j = F(j) - 1)
            res += T[j];
        return res;
    }

    void add(int64_t i, int64_t val)
    {
        for (int64_t j = i; j < T.size(); j = j | (j + 1))
            T[j] += val;
    }

public:
    FenvicTree(const vector<int64_t> &_array)
    {
        array = _array;
        T = vector<int64_t>(array.size(), 0);

        for (int64_t i = 0; i < T.size(); ++i)
        {
            for (int64_t j = F(i); j <= i; ++j)
            {
                T[i] += array[j];
            }
        }
    }

    void set(int64_t i, int64_t val)
    {
        int64_t delta = val - array[i];
        array[i] = val;
        add(i, delta);
    }

    int64_t sum(int64_t l, int64_t r)
    {
        if (l == 0)
            return get(r);
        return get(r) - get(l - 1);
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int64_t> array(n, 0);

    for (int i = 0; i < n; ++i)
        cin >> array[i];

    FenvicTree tree(array);

    string command;
    int val1;
    int val2;

    for (; cin >> command >> val1 >> val2;)
    {
        if (command == "set")
            tree.set(val1 - 1, val2);

        if (command == "sum")
            cout << tree.sum(val1 - 1, val2 - 1) << endl;
    }

    return 0;
}