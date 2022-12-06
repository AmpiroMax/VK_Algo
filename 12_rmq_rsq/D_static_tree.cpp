#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int64_t INF = std::numeric_limits<int64_t>::max();
constexpr int64_t ZERO = 0;

void print(const vector<int64_t> &vec)
{
    for (auto el : vec)
        if (el == INF)
            cout << "i"
                 << " ";
        else
            cout << el << " ";
    cout << endl;
}

class StaticTree
{
private:
    int64_t new_array_size;
    vector<int64_t> tree;
    vector<int64_t> upd_set;
    vector<int64_t> upd_add;

    void build_tree(const vector<int64_t> &array)
    {
        int64_t new_size = 1;
        for (; new_size < array.size(); new_size *= 2)
            ;

        tree = vector<int64_t>(2 * new_size - 1, INF);
        for (int64_t i = 0; i < array.size(); ++i)
            tree[new_size + i - 1] = array[i];

        for (int64_t v = new_size - 2; v >= 0; --v)
            tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);

        new_array_size = new_size;
        upd_add = vector<int64_t>(new_size * 2 - 1, ZERO);
        upd_set = vector<int64_t>(new_size * 2 - 1, INF);
    }

    int64_t get(int64_t v)
    {
        if (upd_add[v] != ZERO && upd_set[v] != INF)
            throw std::runtime_error("ABOBA MISTAKE");

        if (upd_add[v] != ZERO)
            return tree[v] + upd_add[v];

        if (upd_set[v] != INF)
            return upd_set[v];

        return tree[v];
    }

    void push_add(int64_t v, int64_t l, int64_t r)
    {
        if (upd_add[v] == ZERO)
            return;

        if (l == r)
        {
            tree[v] += upd_add[v];
            upd_add[v] = ZERO;
            return;
        }

        if (upd_set[2 * v + 1] != INF)
            upd_set[2 * v + 1] += upd_add[v];
        else
            upd_add[2 * v + 1] += upd_add[v];

        if (upd_set[2 * v + 2] != INF)
            upd_set[2 * v + 2] += upd_add[v];
        else
            upd_add[2 * v + 2] += upd_add[v];

        tree[v] = min(get(2 * v + 1), get(2 * v + 2));
        upd_add[v] = ZERO;
    }

    void push_set(int64_t v, int64_t l, int64_t r)
    {
        if (upd_set[v] == INF)
            return;

        if (l == r)
        {
            tree[v] = upd_set[v];
            upd_set[v] = INF;
            return;
        }

        upd_set[2 * v + 1] = upd_set[v];
        upd_add[2 * v + 1] = ZERO;

        upd_set[2 * v + 2] = upd_set[v];
        upd_add[2 * v + 2] = ZERO;

        tree[v] = min(get(2 * v + 1), get(2 * v + 2));
        upd_set[v] = INF;
    }

    void update_add(int64_t v, int64_t l, int64_t r, int64_t a, int64_t b, int64_t value)
    {
        push_add(v, l, r);
        push_set(v, l, r);

        if (l > b || r < a)
            return;

        if (l >= a && r <= b)
        {
            if (upd_set[v] != INF)
            {
                upd_set[v] += value;
                return;
            }

            upd_add[v] += value;

            return;
        }

        int64_t m = (l + r) / 2;
        update_add(2 * v + 1, l, m, a, b, value);
        update_add(2 * v + 2, m + 1, r, a, b, value);

        tree[v] = min(get(2 * v + 1), get(2 * v + 2));
    }

    void update_set(int64_t v, int64_t l, int64_t r, int64_t a, int64_t b, int64_t value)
    {
        push_add(v, l, r);
        push_set(v, l, r);

        if (l > b || r < a)
            return;

        if (l >= a && r <= b)
        {
            upd_add[v] = ZERO;
            upd_set[v] = value;
            return;
        }

        int64_t m = (l + r) / 2;
        update_set(2 * v + 1, l, m, a, b, value);
        update_set(2 * v + 2, m + 1, r, a, b, value);

        tree[v] = min(get(2 * v + 1), get(2 * v + 2));
    }

    int64_t _RMQ(int64_t v, int64_t l, int64_t r, int64_t a, int64_t b)
    {
        if (l > b || r < a)
            return INF;

        if (l >= a && r <= b)
            return get(v);

        push_add(v, l, r);
        push_set(v, l, r);

        int64_t m = (l + r) / 2;
        return min(_RMQ(2 * v + 1, l, m, a, b), _RMQ(2 * v + 2, m + 1, r, a, b));
    }

public:
    StaticTree(const vector<int64_t> &array)
    {
        build_tree(array);
    }

    void set(int64_t l, int64_t r, int64_t value)
    {
        update_set(0, 0, new_array_size - 1, l, r, value);
    }

    void add(int64_t l, int64_t r, int64_t value)
    {
        update_add(0, 0, new_array_size - 1, l, r, value);
    }

    int64_t RMQ(int64_t l, int64_t r)
    {
        return _RMQ(0, 0, new_array_size - 1, l, r);
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int64_t> array(n, 0);

    for (int i = 0; i < n; ++i)
        cin >> array[i];

    StaticTree tree(array);

    string command;
    int64_t val1;
    int64_t val2;

    for (; cin >> command >> val1 >> val2;)
    {
        if (command == "set")
        {
            int64_t val3;
            cin >> val3;
            tree.set(val1 - 1, val2 - 1, val3);
        }

        if (command == "add")
        {
            int64_t val3;
            cin >> val3;
            tree.add(val1 - 1, val2 - 1, val3);
        }

        if (command == "min")
            cout << tree.RMQ(val1 - 1, val2 - 1) << endl;
    }

    return 0;
}