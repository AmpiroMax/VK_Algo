#include <iostream>
#include <vector>

using namespace std;

const size_t A_MOD = 1 << 16;
const size_t B_MOD = 1 << 30;

class GenerateArray
{
private:
    size_t n;
    size_t x;
    size_t y;
    size_t a0;
    size_t modulo;
    vector<size_t> array;

    size_t calculate(size_t i)
    {
        return (x * array[i - 1] + y) % modulo;
    }

    void generate()
    {
        for (size_t i = 1; i < n; ++i)
        {
            array[i] = calculate(i);
        }
    }

public:
    GenerateArray(size_t _n, size_t _x, size_t _y, size_t _a0, size_t _modulo)
    {
        n = _n;
        x = _x;
        y = _y;
        a0 = _a0;
        modulo = _modulo;
        array = vector<size_t>(n, a0);
        generate();
    }

    vector<size_t> get_array()
    {
        return array;
    }
};

int main()
{
    size_t n;
    size_t x;
    size_t y;
    size_t a0;

    cin >> n >> x >> y >> a0;
    vector<size_t> prefix_sum = GenerateArray(n, x, y, a0, A_MOD).get_array();
    for (size_t i = 1; i < n; ++i)
        prefix_sum[i] += prefix_sum[i - 1];

    size_t m;
    size_t z;
    size_t t;
    size_t b0;

    cin >> m >> z >> t >> b0;
    vector<size_t> tmp_requests = GenerateArray(2 * m, z, t, b0, B_MOD).get_array();
    vector<size_t> requests(2 * m, 0);

    for (size_t i = 0; i < 2 * m; ++i)
        requests[i] = tmp_requests[i] % n;

    size_t result = 0;
    for (size_t i = 0; i < m; ++i)
    {
        size_t l = min(requests[2 * i], requests[2 * i + 1]);
        size_t r = max(requests[2 * i], requests[2 * i + 1]);

        size_t delta = 0;
        if (l == 0)
            delta = prefix_sum[r];
        else
            delta = prefix_sum[r] - prefix_sum[l - 1];

        result += delta;
    }
    cout << result << endl;
    return 0;
}