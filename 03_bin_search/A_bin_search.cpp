#include <iostream>
#include <vector>

using namespace std;

int lower_bound(const vector<int> &mass, int x)
{
    int l = -1;
    int r = mass.size();

    while (l < r - 1)
    {
        int m = (l + r) / 2;
        if (x <= mass[m])
            r = m;
        else
            l = m;
    }
    return r;
}

int main()
{
    int n;
    int k;
    cin >> n >> k;

    vector<int> mass;
    for (int i = 0; i < n; ++i)
    {
        int el;
        cin >> el;
        mass.push_back(el);
    }

    for (int i = 0; i < k; ++i)
    {
        int el;
        cin >> el;
        int r = lower_bound(mass, el);

        if (r == 0)
        {
            cout << mass[0] << endl;
        }
        else if (abs(mass[r] - el) < abs(mass[r - 1] - el))
        {
            cout << mass[r] << endl;
        }
        else
        {
            cout << mass[r - 1] << endl;
        }
    }

    return 0;
}