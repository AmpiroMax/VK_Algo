#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<size_t> &vec)
{
    for (auto el : vec)
        cout << el << " ";
    cout << endl;
}

class GenerateArray
{
private:
    size_t n;
    size_t a0;
    vector<size_t> array;

    size_t calculate(size_t i)
    {
        return (23 * array[i - 1] + 21563) % 16714589;
    }

public:
    GenerateArray(size_t _n, size_t _a0)
    {
        n = _n;
        a0 = _a0;

        array = vector<size_t>(n, a0);
        for (size_t i = 1; i < n; ++i)
            array[i] = calculate(i);
    }

    vector<size_t> get_array()
    {
        return array;
    }
};

class SparseTable
{
private:
    vector<vector<size_t>> minimum;
    vector<size_t> precalc_k;

    void preproc()
    {
        for (size_t k = 1; k < minimum[0].size(); ++k)
        {
            for (size_t l = 0; l < minimum.size(); ++l)
            {
                if (l + (1 << (k - 1)) < minimum.size())
                {
                    minimum[l][k] = min(
                        minimum[l][k - 1],
                        minimum[l + (1 << (k - 1))][k - 1]);
                }
                else
                {
                    minimum[l][k] = minimum[l][k - 1];
                }
            }
        }
    }

public:
    SparseTable(size_t n, const vector<size_t> &array)
    {

        precalc_k = vector<size_t>(n, 0);
        for (size_t i = 1; i < n; ++i)
        {
            precalc_k[i] = precalc_k[i - 1];

            if ((2 << precalc_k[i]) <= i)
                precalc_k[i] += 1;
        }

        minimum = vector<vector<size_t>>(n, vector<size_t>(precalc_k[n - 1] + 1, -1));

        for (size_t i = 0; i < n; ++i)
        {
            minimum[i][0] = array[i];
        }

        preproc();
    }

    size_t RMQ(size_t l, size_t r)
    {
        size_t k = precalc_k[r - l];
        return min(minimum[l][k], minimum[r - (1 << k) + 1][k]);
    }
};

int main()
{
    int n;
    int m;
    int a0;
    int u1;
    int v1;
    cin >> n >> m >> a0 >> u1 >> v1;

    vector<size_t> array = GenerateArray(n, a0).get_array();
    SparseTable table(n, array);

    for (size_t i = 1; i <= m; ++i)
    {
        auto [l, r] = std::minmax(u1, v1);

        size_t value = table.RMQ(l - 1, r - 1);

        if (i == m)
            cout << u1 << " " << v1 << " " << value << endl;

        u1 = ((17 * u1 + 751 + value + 2 * i) % n) + 1;
        v1 = ((13 * v1 + 593 + value + 5 * i) % n) + 1;
    }

    return 0;
}